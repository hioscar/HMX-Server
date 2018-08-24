#ifndef __CLIENT_NET_HANDLER_H_
#define __CLIENT_NET_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

class Player;

/*
 *
 *	Detail: �ͻ���Handler�¼�
 *   
 *  Created by hzd 2015/01/26  
 *
 */
class PlayerProcHandler : public Single<PlayerProcHandler>
{
public:

	PlayerProcHandler(void);
	~PlayerProcHandler(void);

	// �����ɷ����������Ͽ� 
	static void SendRequestClose(Player* player);

	/////////////////////////////����/////////////////////////////////////////////
	static void SendEncrypt(Player* player);
	static void SendLogin(Player* player);
	static void SendLogin2(Player* player);
	static void SendRandName(Player* player);
	static void SendCharacterList(Player* player);
	static void SendRoleCreate(Player* player);
	static void SendRoleDelete(Player* player);
	static void SendChar2World(Player* player);
	static void SendLoadResed(Player* player);

	static void SendReqSceneData(Player* player); 

	static void SendSelectRole(Player* player);

	static void SendEnterChangeScene(Player* player);
	static void SendEnterChangeScene2(Player* player);

	static void SendMoveTo(Player* player);
	static void SendChatToWorld(Player* player);

	static void SendRelationList(Player* player);
	static void SendRelationAdd(Player* player);
	static void SendRelationRmove(Player* player);


	/////////////////////////////����/////////////////////////////////////////////

	void RecvEncryptInfo(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvLoginReadyFinish(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvEnterScene(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvChatWorld(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvSceneInitResult(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvRandNames(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);

	void RecvRelationList(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvRelationUpdate(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvRelationDelete(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvUserPackages(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	

	//////////////////////////////////////////////////////////////////////////
	void RecvLoginAccountResult(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvCharacterList(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvRoleCreateResult(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvCharacterMainData(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvQuestMainData(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvSendDataFinish(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvEnterSceneInfo(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);

	void RecvChannelJion(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);
	void RecvChannelLeave(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize);

};

#endif

