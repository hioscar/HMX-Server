#ifndef _SERVER_MSG_HANDLER_H_
#define _SERVER_MSG_HANDLER_H_

#include "Includes.h"
#include "NetConfig.h"
#include "SrvEngine.h"

class NetMsgHandler : public zMsgHandler, public Single<NetMsgHandler>
{
public:
	NetMsgHandler();
	~NetMsgHandler();
	void OnNetMsgEnter(NetSocket& rSocket);
	void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize);
	void OnNetMsgExit(NetSocket& rSocket);

	// �ɶ�������������¼��ע��serverid��
	void recvLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void recvLoginReponse(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// �ɶ��������Ping
	void recvPingRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// �������б� 
	void recvSrvListNotifty(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	
};

#endif


