#include "GameService.h"
#include "NetIncludes.h"
#include "NetMsgHandler.h"
#include "DBConnection.h"
#include "CSortsManager.hpp"
#include "COnlineRecord.h"
#include "MyHttpServer.h"
#include "WorldUserMgr.h"
#include "OfflineUserMgr.h"
#include "MessageMgr.h"
#include "SceneRoomMgr.h"

GameService::GameService()
	:zNetSerivce(H::logger->getName())
{
	mWorldUserMgr = new WorldUserMgr();
	mOfflineUserMgr = new OfflineUserMgr();
	mMessageMgr = new MessageMgr();
	mSceneRoomMgr = new SceneRoomMgr();
}

GameService::~GameService()
{

}

bool GameService::run()
{
#ifdef WIN32
	Sleep(MAIN_LOOP_TIME);
#else
	usleep(MAIN_LOOP_TIME);
#endif
	return true;
}

void GameService::finaly()
{

}


bool GameService::doBindServer(const ::config::SerivceInfo& info)
{
	bool bResult = SessionMgr()->bind(this,info,
		boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
		boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
		boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
		);
	if (!bResult)
	{
		H::logger->error("Bind Server Fail!");
		ASSERT(0);
		return false;
	}
	return true;
}

bool GameService::doConnectServer(const ::config::SerivceInfo& info)
{
	zSession* session = SessionMgr()->connect(this,info,
		boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
		boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
		boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
		);
	if (!session)
	{
		H::logger->error("Connect Server Fail!");
		ASSERT(0);
		return false;
	}
	return true;
}

void GameService::netioUpdate(const zTaskTimer* timer)
{
	/* ��ws,fep,dp֮ǰsocket��ʱ����IO��Ϣ��������ϢЭ��Ĵ���  */
	SessionMgr()->updateIO(timer);

	/* ��Ҷ�ʱ��������Ҫ��ʱ���¼�(ҵ���߼�) */
	if (timer->is1Min())
	{
		pingToServer();
	}
}

boost::asio::io_service* GameService::GetIoService()
{
	return  SessionMgr()->GetNetServer(1);
}

bool GameService::init()
{
	bool bResult = SrvSerivceMgr()->LoadConfig(H::global["confdir"] + "/serivces.xml");
	if (!bResult)
	{
		H::logger->error("Load serivces.xml fail,path=%s", "serivces.xml");
		return false;
	}

	zServerMgr* pSrvMgr = SrvSerivceMgr()->GetServerMgr(GetServerID());
	if (!pSrvMgr)
	{
		H::logger->error("Not found serverID=%u serivces.xml", GetServerID());
		return false;
	}

	if (!pSrvMgr->StartSerivces(this))
	{
		H::logger->error("Server Start Fail!");
		return false;
	}

	app = new MyHttpServer("WS_HTTP_SERVER",8090);
	app->start();

	// Ԥ�ȼ������� 
	mOfflineUserMgr->loadDB();
	CSortsManager::Instance()->loadDB();

	COnlineRecord::Instance()->Init();
	CSortsManager::Instance()->Init();

	H::logger->info("Server Start Success !");

	return true;
}

int GameService::CheckMd5(int64_t accid, int32_t keytime, const char* keymd5)
{
	// У��md5
	std::ostringstream outstr;
	outstr << accid;
	outstr << "maj2017";
	outstr << keytime;

	char md5str[33] = { 0 };
	EncryptMD5str(md5str,outstr.str().c_str(), outstr.str().length());

	if (STRNICMP(md5str, keymd5, 32) != 0)
	{
		H::logger->error("Md5����ʧ�ܣ���Կ��ƥ�� ��Ҫ:%s,����:%s", md5str, keymd5);
		return 1;
	}

	if (keytime + 86400 < time(NULL))
	{
		H::logger->error("Md5����ʧ��,ʱ�����");
		return 2;
	}

	H::logger->info("Md5����ɹ�!");

	return 0;
}

/* ���� -c cfg.xml -l ��־�ļ�  */ 
int main(int argc, const char * argv[])
{
	H::logger = new zLogger("WorldServer");
	H::logger->addLocalFileLog("./ws");

	/* ����ȱʡ����  */
	H::global["datadir"] = "data/";
	H::global["confdir"] = "conf/";
	H::global["questdir"] = "quest/";
	H::global["mail_service"] = "on";
	H::global["log"] = "debug";

	H::logger->setLevel(H::global["log"]);

	H::global["confdir"] = (argc >= 2 ? argv[1] : ".");
	H::global["serverid"] = "3001";

	GameService::getMe().main();
	GameService::delMe();

	return 0;
}



