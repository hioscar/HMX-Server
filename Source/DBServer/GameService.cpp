#include "GameService.h"
#include "SrvIncludes.h"
#include "NetIncludes.h"
#include "NetMsgHandler.h"
#include "CZhanJiRecordMgr.hpp"

GameService::GameService() 
	:zNetSerivce(H::logger->getName())
{

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
	bool bResult = SessionMgr()->bind(this, info,
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
	zSession* session = SessionMgr()->connect(this, info,
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

	CZhanJiRecordMgr::getMe().LoadRecords();

	return true;
}

/* ���� -c cfg.xml -l ��־�ļ�  */ 
int main(int argc, const char * argv[])
{
	H::logger = new zLogger("DBServer");
	H::logger->addLocalFileLog("./dp");
	/* ����ȱʡ����  */
	H::global["datadir"] = "data/";
	H::global["confdir"] = "conf/";
	H::global["questdir"] = "quest/";
	H::global["mail_service"] = "on";
	H::global["log"] = "debug";

	H::logger->setLevel(H::global["log"]);

	H::global["confdir"] = (argc >= 2 ? argv[1] : ".");
	H::global["serverid"] = "5001";

	GameService::getMe().main();
	GameService::delMe();

	return 0;
}



