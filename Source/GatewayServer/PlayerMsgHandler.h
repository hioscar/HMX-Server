#ifndef CLIENT_MSG_HANDLER_H_
#define CLIENT_MSG_HANDLER_H_


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
// ���״̬ 
enum EClientStatus
{
	/*-------------------------------------------------------------------
	* @Brief : ��ʼ��ʱ����Client���ӳɹ�ʱ����ʼ����Sessionʱ
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_INITED = 0,	// 

	/*-------------------------------------------------------------------
	* @Brief : ��ʼ����ɺ�����Ϊ�Ѿ����ӳɹ�״̬��
	*          ��ʱ����������Կ�ӿ�
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_CONNECTED,

	/*-------------------------------------------------------------------
	* @Brief : �Ѿ���������Կ�ɹ�����ʱ��Client�ǲ��������κνӿڵģ�
	*          ��ʱ���������������为����͵�dp,ls������ID
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_ENCRYPTED,	// �����Կ�ɹ���� 

	/*-------------------------------------------------------------------
	* @Brief : ����ls,dp������id�ɹ�����ʱclient��������ls�����ʺŵ�¼
	*
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_NOTIFY_INITED,

	/*-------------------------------------------------------------------
	* @Brief :
	*
	*------------------------------------------------------------------*/
	E_CLIENT_STATUS_LOGINED,	// ��¼������ 
	E_CLIENT_STATUS_SELECTED,	// ѡ���ɫ��� 
	E_CLIENT_STATUS_IN_WORLD,	// ���Խ������ݽ������  
	E_CLIENT_STATUS_IN_SCENE,	// ����Ϸ������ 
};


/*-------------------------------------------------------------------
 * @Brief : ���մ���ͻ��ˣ��û�������
 *			�̶��Ŀͻ������ݴ�������Э����Proc��
 * 
 * @Author:hzd 2013/04/03
 *------------------------------------------------------------------*/
class PlayerMsgHandler : public zMsgHandler, public Single<PlayerMsgHandler>
{
public:
	PlayerMsgHandler();
	~PlayerMsgHandler();

	// �пͻ������ӻص� 
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// �пͻ�����Ϣ�յ� 
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32_t nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����)  
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// ���͵� ls
	void ReqSendToLoginServer(zSession* pSession,const NetMsgSS* pMsg,int32_t nSize);

	// ���͵� ss
	void ReqSendToSceneServer(zSession* pSession,const NetMsgSS* pMsg,int32_t nSize);

	// ���͵� ws
	void ReqSendToWorldServer(zSession* pSession,const NetMsgSS* pMsg,int32_t nSize);

	// ���͵� player 
	void SendToPlayer(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);

	//-----------------------------���ش���Э��---------------------------------
	// fep
	void ReqFepEncyptHandler(zSession* pSession,const NetMsgSS* pMsg,int32_t nSize);

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



