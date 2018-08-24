#ifndef _SCENE_SERVER_MSG_HANDLER_H_
#define _SCENE_SERVER_MSG_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

struct NetMsgSS;

class ProcSsHandler : public Single<ProcSsHandler>
{
public:
	ProcSsHandler();
	~ProcSsHandler();

	// �����ɻ������滻
	void onStartRobotReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	// �����ɻ������滻
	void onStopRobotReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void RobotReconnResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void RobotStartRoundResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void NtBroadcastMsg(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	/* ������Ϣת�� */
	void TurnChatToOne(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void UpdateUserToGate(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);


};

#endif


