#include "ProcFepHandler.h"

#include "GameService.h"
#include "WorldUser.h"
#include "WorldUserMgr.h"
#include "SceneRegMgr.h"
#include "MessageMgr.h"
#include "MysqlProtobufHelper.h"
#include "base/hmx_data.pb.h"
#include "curl.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/StreamCopier.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/PrintHandler.h"

#include "LoginTokenMgr.h"

using namespace Poco::Dynamic;
using namespace Poco;

ProcFepHandler::ProcFepHandler()
{

}


ProcFepHandler::~ProcFepHandler()
{

}

void ProcFepHandler::HandleLoginOut(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

}

void ProcFepHandler::HandleLoginPlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	const zServerMgr* pSrvMgr = GameService::getMe().SrvSerivceMgr()->GetServerMgr(GameService::getMe().GetServerID());
	if (pSrvMgr == NULL)
	{
		H::logger->error("Not found zServerMgr");
		return;
	}

	::msg_maj::LoginPlayerReq proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);

	std::string platUrl = pSrvMgr->GetPlatUrl();
	char destUrl[1024] = { 0 };
	sprintf(destUrl, "%s/getProxyGames?account=%s", pSrvMgr->GetPlatUrl().c_str(), proto.account().c_str());

	CurlParm* parm = new CurlParm();
	parm->conn = pSession;
	parm->account = proto.account();
	parm->sessionID = pMsg->clientSessID;
	parm->param_val = proto.serverid();

	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();    // 初始化
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, destUrl);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &onProxyGameZone);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, parm);
		res = curl_easy_perform(curl);   // 执行
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	
}

size_t onProxyGameZone(void *buffer, size_t size, size_t nmemb, void *parm)
{
	CurlParm* pParm = (CurlParm*)parm;
	if (NULL == pParm)
	{
		return 0;
	}

	int16_t dataLength = (size * nmemb);
	pParm->buff_times++;
	memcpy(&pParm->buffer[pParm->buff_length], (char*)buffer, dataLength);
	pParm->buff_length += dataLength;

	std::string jsonStrSrc((char*)pParm->buffer, pParm->buff_length);
	zSession* pSession = pParm->conn;
	std::string account = pParm->account;
	uint32_t clientSessionID = pParm->sessionID;

	delete pParm;
	pParm = NULL;

	JSON::Parser parser;
	Dynamic::Var result;
	parser.reset();

	result = parser.parse(jsonStrSrc);
	JSON::Object::Ptr pObj = result.extract<JSON::Object::Ptr>();
	int status = atoi(pObj->get("status").toString().c_str());
	if (status != ::msg_maj::SUCCESS)
	{
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code((::msg_maj::login_code)status);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
		return 0;
	}

	JSON::Array::Ptr pObjArr = pObj->getArray("game_ids");
	
	std::vector<int32_t> game_list;
	for (JSON::Array::ConstIterator it = pObjArr->begin(); it != pObjArr->end(); ++it)
	{
		const Dynamic::Var& var = *it;
		game_list.push_back(atoi(var.toString().c_str()));
	}

	// 检查是否可以登录
	std::vector<int32_t>::const_iterator it2 = std::find(game_list.begin(), game_list.end(),pParm->param_val);
	if (it2 == game_list.end())
	{
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code(::msg_maj::NOT_BING_SERVER);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
		return 0;
	}

	// 可进入的服务器列表
	if (game_list.empty()) {
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code(::msg_maj::NOT_BING_SERVER);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
		return 0;
	}

	// 加载帐号并登录到场景服
	db::DBConnection* dbData = GameService::getMe().GetDataRef();
	if (dbData == NULL)
	{
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code(::msg_maj::MYSQL_ISNULL);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
		return 0;
	}

	uint32_t uid = atol(pObj->get("uid").toString().c_str());

	std::stringstream dataWsSql;
	dataWsSql << "select `id`,`account`,`nickname`,`logo_icon`,`room_card`,`total_games`,`win_games`,`his_max_con`,`his_max_score`,`top_score_total` from `tb_role` WHERE id=" << uid << ";";
	::msg_maj::RoleWs roleWs;
	int ret = doQueryProto(*dbData, dataWsSql.str(), roleWs);
	if (ret != 0)
	{
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code(::msg_maj::SQL_ERROR);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
		return 0;
	}

	const ::msg_maj::LoginToken* loginToken = LoginTokenMgr::Instance()->GetToken(account);
	if (loginToken == NULL)
	{
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code(::msg_maj::WSUSER_IS_NULL);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
		return 0;
	}

	if (roleWs.id() < 1)
	{
		// 创建角色
		::msg_maj::Role m_proData;

		m_proData.Clear();

		char nickname[32];
		memset(nickname, 0, sizeof(nickname));

		int32_t level = 1;
		std::string logo_icon = "";

		m_proData.set_id(uid);
		m_proData.set_account(account);
		m_proData.set_nickname(loginToken->nickname());
		m_proData.set_level(1);
		m_proData.set_logo_icon(loginToken->headimgurl());
		m_proData.set_title(0);
		m_proData.set_diamond(0);
		m_proData.set_coin(0);
		m_proData.set_sexual(0);
		m_proData.set_room_card(5);
		m_proData.set_total_games(0);
		m_proData.set_win_games(0);
		m_proData.set_con_games(0);
		m_proData.set_his_max_score(0);
		m_proData.set_his_max_con(0);
		m_proData.set_week_max_score(0);
		m_proData.set_top_wins_ymd(0);
		m_proData.set_top_wins_total(0);
		m_proData.set_top_score_ymd(0);
		m_proData.set_top_score_total(0);
		m_proData.set_blocktime(0);
		m_proData.set_login_time(time(NULL));

		std::stringstream smData;
		smData << "replace into tb_role(id, account, nickname, level, logo_icon, title, diamond, coin,sexual, room_card, total_games, win_games, con_games, "
			<< "his_max_score,his_max_con, week_max_score, top_wins_ymd, top_wins_total, top_score_ymd, top_score_total, blocktime, login_time, data) values("
			<< m_proData.id() << ", "
			<< db::StringMysqlString(dbData->getMysqlRef(), m_proData.account()) << ", "
			<< db::StringMysqlString(dbData->getMysqlRef(), m_proData.nickname()) << ", "
			<< m_proData.level() << ", "
			<< db::StringMysqlString(dbData->getMysqlRef(), m_proData.logo_icon()) << ", "
			<< m_proData.title() << ", "
			<< m_proData.diamond() << ", "
			<< m_proData.coin() << ", "
			<< m_proData.sexual() << ", "
			<< m_proData.room_card() << ", "
			<< m_proData.total_games() << ", "
			<< m_proData.win_games() << ", "
			<< m_proData.con_games() << ", "
			<< m_proData.his_max_score() << ", "
			<< m_proData.his_max_con() << ", "
			<< m_proData.week_max_score() << ", "
			<< m_proData.top_wins_ymd() << ", "
			<< m_proData.top_wins_total() << ", "
			<< m_proData.top_score_ymd() << ", "
			<< m_proData.top_score_total() << ", "
			<< m_proData.blocktime() << ", "
			<< m_proData.login_time() << ", "
			<< db::ProtoMysqlString(dbData->getMysqlRef(), m_proData.data()) << ")";
		int32_t nRet = db::doQuery(*dbData, smData.str());
		if (nRet == 0)
		{
			//LOG(INFO) << "SavePlayerDataTask success!";
		}
		else
		{
			//LOG(ERROR) << "SavePlayerDataTask failure!";
			H::logger->error("SavePlayerDataTask failure!");
			ASSERT(0);
		}

		doQueryProto(*dbData, dataWsSql.str(), roleWs);

		db::DBConnection* dbLog = GameService::getMe().GetLogRef();
		if (dbLog)
		{
			// 记录注册
			std::stringstream smRegister;
			smRegister << "insert into tb_register(uid, time, channel) values(" << m_proData.id() << ", " << time(NULL) << ",0);";
			db::doQuery(*dbLog, smRegister.str());
		}

	}
	else //更新名字和头像
	{
		std::stringstream roleSql;
		roleSql << "update tb_role set ";
		roleSql << " login_time=" << time(NULL);
		roleSql << ",nickname=" << db::StringMysqlString(dbData->getMysqlRef(), loginToken->nickname());
		roleSql << ",logo_icon=" << db::StringMysqlString(dbData->getMysqlRef(), loginToken->headimgurl());
		roleSql << ",ip=" << loginToken->ip();
		roleSql << " where id = " << roleWs.id();
		doQuery(*dbData, roleSql.str());
	}

	if (roleWs.id() < 1)
	{
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code(::msg_maj::SQL_ERROR);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
		return 0;
	}

	zSession* pScene = GameService::getMe().SessionMgr()->getSs(pParm->param_val);
	if (pScene == NULL)
	{
		::msg_maj::LoginPlayerResp loginResp;
		loginResp.set_code(::msg_maj::SCENE_NOT_FOUND);
		loginResp.set_srv_time(time(NULL));
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, loginResp);
		return 0;
	}

	WorldUser* wsUser = GameService::Instance()->GetWorldUserMgr()->AddUser(roleWs, clientSessionID);
	if (wsUser == NULL) // 发现有相同的角色ID，踢掉旧的session
	{
		wsUser = GameService::Instance()->GetWorldUserMgr()->getByUID(roleWs.id());
		if (wsUser == NULL)
		{
			::msg_maj::LoginPlayerResp loginResp;
			loginResp.set_code(::msg_maj::WSUSER_IS_NULL);
			loginResp.set_srv_time(time(NULL));
			pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, clientSessionID, loginResp);
			return 0;
		}

		::msg_maj::LoginToScene sendLogin;
		sendLogin.set_uid(wsUser->GetID());
		sendLogin.set_repeat_login(true);
		sendLogin.set_new_session_id(clientSessionID);
		wsUser->sendMsgToSs(::comdef::msg_ss, ::msg_maj::login_to_scene_req, sendLogin);

		wsUser->SetClientSessID(clientSessionID);
		wsUser->SetFepSession(pSession);
		wsUser->SetSceneSession(pScene);
		wsUser->refreshProxyServerList(game_list);
	}
	else
	{
		wsUser->SetFepSession(pSession);
		wsUser->SetSceneSession(pScene);
		wsUser->refreshProxyServerList(game_list);

		::msg_maj::LoginToScene sendLogin;
		sendLogin.set_uid(wsUser->GetID());
		sendLogin.set_repeat_login(false);
		sendLogin.set_new_session_id(0);
		wsUser->sendMsgToSs(::comdef::msg_ss, ::msg_maj::login_to_scene_req, sendLogin);
	}

	db::DBConnection* dbLog = GameService::getMe().GetLogRef();
	if (dbLog)
	{
		std::stringstream smLogin;
		smLogin << "insert into tb_login(uid, time) values(" << wsUser->GetID() << ", " << time(NULL) << ");";
		db::doQuery(*dbLog, smLogin.str());
	}

	return 0;
}

void ProcFepHandler::doLoginTask(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

}

void ProcFepHandler::HandlePlayerExit(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	WorldUser* wsUser = GameService::getMe().GetWorldUserMgr()->getBySessID(pMsg->clientSessID);
	if (wsUser == NULL)
	{
		return;
	}
	GameService::getMe().GetWorldUserMgr()->OfflineUser(wsUser);
}

void ProcFepHandler::doSelectRole(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

}

void ProcFepHandler::doCreateRole(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

}

void ProcFepHandler::doDeleteRole(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{

}

void ProcFepHandler::doMessageTask(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	GameService::getMe().GetMessageMgr()->doUserCmd(pSession, pMsg, nSize);
}
