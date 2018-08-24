#ifndef _WEB_MSG_HANDLER_H_
#define _WEB_MSG_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

class NetSocket;
struct NetMsgSS;

/*------------------------------------------------------------------
*
* @Brief : ͨ������Server�Ŀͻ���Session��ֻ�����ڼ�¼ͨ�õ���Ϣ
*          ���಻���޸�������Ϸ���ܣ�ֻ������Ϸ����޸�
* @Author: hzd
* @File  : ClientSession.h
* @Date  : 2015/10/18 22:33
* @Copyright (c) 2015,hzd, All rights reserved.
*-----------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * @Brief : ���մ���ͻ��ˣ��û�������
 *			�̶��Ŀͻ������ݴ�������Э����Proc��
 * 
 * @Author:hzd 2013/04/03
 *------------------------------------------------------------------*/
class WebMsgHandler : public zMsgHandler, public Single<WebMsgHandler>
{
public:
	WebMsgHandler();
	~WebMsgHandler();

	virtual void OnNetMsgEnter(NetSocket& rSocket) {};
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize){};
	virtual void OnNetMsgExit(NetSocket& rSocket) {};

	// �пͻ������ӻص� 
	virtual void OnWebMsgEnter(CWebClient* client);

	// �пͻ�����Ϣ�յ� 
	virtual void OnWebMsg(CWebClient* client, PbMsgWebSS* pMsg,int32_t nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����)  
	virtual void OnWebMsgExit(CWebClient* client);

	// ���͵� local
	void ReqSendLocalServer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	// ���͵� ls
	void ReqSendToLoginServer(zSession* pSession,const PbMsgWebSS* pMsg,int32_t nSize);

	// ���͵� ss
	void ReqSendToSceneServer(zSession* pSession,const PbMsgWebSS* pMsg,int32_t nSize);

	// ���͵� ws
	void ReqSendToWorldServer(zSession* pSession,const PbMsgWebSS* pMsg,int32_t nSize);

	// ���͵� player 
	void SendToPlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	//-----------------------------���ش���Э��---------------------------------

	//////////////////////////////////////////////////////////////////////////
	virtual bool ForWsOnExit(NetSocket& rSocket) { return true; };
	virtual bool ForClientToServerOnMsgEnter(NetSocket& rSocket, int32_t nLocalServerType) { return true; };
	virtual bool ForServerOnMsgEnter(NetSocket& rSocket, int32_t nServerType) { return true; };
	virtual bool ForServerOnMsgExit(NetSocket& rSocket) { return true; };
	virtual bool ForServerOnLogin(zSession* pSession, const NetMsgSS* pMsg) { return true; };
	virtual bool ForServerTimeOutCancel(zSession* pSession) { return true; };
	virtual bool ForWsUpdateClientToFepDp(zSession* pSession, const NetMsgSS* pMsg, int32_t nOnServerType) { return true; };

	virtual bool ForWsOnMsgEnter(NetSocket& rSocket, int32_t nLocalServerType) { return true; };
	virtual bool ForWsOnMsg(zMsgHandler& baseMsgHandler, NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize) { return true; };
	virtual bool ForWsUpdateClientToLsSs(zSession* pSession, const NetMsgSS* pMsg, int32_t nOnServerType) { return true; };
	virtual bool ForServerOnMsg(zMsgHandler& baseMsgHandler, NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize) { return true; };

};

/*-------------------------------------------------------------------
 * @Brief : ���ͻ��˷�������Ϣת��SSͨ����Ϣ����Ϣͷ������clientSessionID��
 * 
 * @Author:hzd 2015:10:24
 *------------------------------------------------------------------*/
#define MSG_MAKE_PLAYER_SESSID(_sessid,_fepsid,pMsg,nSize) static vector<char> vecMsgBuffer;\
{\
	vecMsgBuffer.resize(nSize); \
	memcpy(&vecMsgBuffer[0], pMsg, nSize); \
	reinterpret_cast<NetMsgSS*>(&vecMsgBuffer[0])->clientSessID = _sessid; \
	reinterpret_cast<NetMsgSS*>(&vecMsgBuffer[0])->fepServerID = _fepsid; \
}\


#endif



