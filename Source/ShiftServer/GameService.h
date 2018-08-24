#ifndef __SCENES_SERVICE_H_
#define __SCENES_SERVICE_H_

#include "SrvEngine.h"
#include "DbMysql.h"
#include "Includes.h"

class GameService : public zNetSerivce, public Single<GameService>
{
protected:
	friend class Single<GameService>;
	GameService();
	~GameService();
	virtual bool init();
	virtual bool run();
	virtual void finaly();

	void netioUpdate(const zTaskTimer* timer);
	void timerTickUpdate(const zTaskTimer* timer);

	void pingToServer();

public:

	int32 getServerID()
	{
		return serverID;
	}

	int32 getServerType()
	{
		return serverType;
	}

	DbMysql* getDbMysql()
	{
		return dbCoon;
	}

	zSessionMgr& getSessionMgr()
	{
		return sessionMgr;
	}

	zSerivceCfgMgr& getServerCfgMgr()
	{
		return serverCfgMgr;
	}

	zServerRegMgr& getServerRegMgr()
	{
		return serverRegMgr;
	}


private:

	int32 serverID;
	int32 serverType;

	DbMysql* dbCoon;
	zSessionMgr sessionMgr;
	zSerivceCfgMgr serverCfgMgr;
	zServerRegMgr serverRegMgr;

	zTaskTimer* netioTaskTimer;
	zTaskTimer*	timeTickTaskTimer;

};



#endif
