#include "PlayerMsgHandler.h"
#include "GameService.h"
#include "GateScene.h"
#include "GateUser.h"


// �� fep �� ��client��sessionIDΪsocketID

PlayerMsgHandler::PlayerMsgHandler() :zMsgHandler(GameService::Instance())
{

	// to fep
#define REGISTER_FEP_MESSAGE(msg_idx, cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls),boost::bind(&PlayerMsgHandler::handler, this, _1, _2,_3)); \
	}

//	REGISTER_FEP_MESSAGE(C::RQ_ENCRYPT, C::RqEncryptInfo,	ReqFepEncyptHandler);

#undef REGISTER_FEP_MESSAGE

	// to ls
#define REGISTER_LS_MESSAGE(msg_idx,cls)\
	{\
	RegisterMessage(msg_idx,sizeof(cls),boost::bind(&PlayerMsgHandler::ReqSendToLoginServer,this, _1, _2,_3));\
	}
	
	//REGISTER_LS_MESSAGE(C::RQ_ACCOUNT_LOGIN, C::RqAccountLogin);
	
#undef REGISTER_LS_MESSAGE

	// to ws
#define REGISTER_WS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToWorldServer, this, _1, _2,_3)); \
	}

	//REGISTER_WS_MESSAGE(C::RQ_SWITCH_SCENE, C::RqSwitchScene);	// �л��³��� 
	//REGISTER_WS_MESSAGE(C::RQ_Rq_SELECT_ROLE, C::RqSelectRole);		// ѡ���ɫ
	//REGISTER_WS_MESSAGE(C::RQ_CREATE_ROLE, C::RqCreateRole);
	//REGISTER_WS_MESSAGE(C::RQ_DELETE_ROLE, C::RqDeleteRole);

	//REGISTER_WS_MESSAGE(C::RQ_LOOK_MESSAGE,	C::rqLookMessage);
	//REGISTER_WS_MESSAGE(C::RQ_OPT_MESSAGE, C::rqOptMessage);

#undef REGISTER_WS_MESSAGE

	// to ss
#define REGISTER_SS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToSceneServer, this, _1, _2,_3)); \
	}

	//REGISTER_SS_MESSAGE(RQ_CHAT_WORLD,		RqCharWorld);
	//REGISTER_SS_MESSAGE(C::RQ_SCENE_INIT_DATA, C::RqClientIsReady);
	//REGISTER_SS_MESSAGE(C::RQ_CHANGE_SCENE, C::RqChanageScene);

	//REGISTER_SS_MESSAGE(C::RQ_ITEM_MOVE_POSITION, C::RqItemMovePosition);
	//REGISTER_SS_MESSAGE(C::RQ_POSITION_MOVE, C::RqPositionMove);
	//REGISTER_SS_MESSAGE(C::RQ_ITEM_USE_OBJECT, C::RqItemUseObject);

	//REGISTER_SS_MESSAGE(C::RQ_SHOPPING_BUY_ITME, C::RqShoppingBuyItem);
	//REGISTER_SS_MESSAGE(C::RQ_SHOPPING_SELL_ITME, C::RqShoppingSellItem);

	//REGISTER_SS_MESSAGE(C::RQ_CHAT_TO_WORLD, C::RqChatToWorld);

	//REGISTER_SS_MESSAGE(C::RQ_RELATION_LIST, C::RqRelationList);
	//REGISTER_SS_MESSAGE(C::RQ_RELATION_ADD, C::RqRelationAdd);
	//REGISTER_SS_MESSAGE(C::RQ_RELATION_REMOVE, C::RqRelationRemove);

#undef REGISTER_SS_MESSAGE

}


PlayerMsgHandler::~PlayerMsgHandler()
{
}

void PlayerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("[���]���ӳɹ���������:id=%d ip=%s,port=%d", rSocket.SocketID(), rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());

	zSession* session = GameService::getMe().PlayerSessMgr()->get(rSocket.SocketID());
	if (session)
	{
		session->initEncrypt();
		zSession* ws = GameService::getMe().PlayerSessMgr()->getWs();
		if (ws == NULL)
		{
			H::logger->warn("[���]WS��δ���ӣ��ܾ��������");
			session->socket->OnEventColse();
			return;
		}

		zSession* ls = GameService::getMe().SessionMgr()->getLs();
		if (ls == NULL)
		{
			H::logger->warn("[���]LS��δ���ӣ��ܾ��������");
			session->socket->OnEventColse();
			return;
		}
		session->status = E_CLIENT_STATUS_CONNECTED;
	}
	else
	{
		H::logger->error("[���]�Ҳ���Session");
	}
}


void PlayerMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32_t nSize)
{
	zSession* session = GameService::getMe().PlayerSessMgr()->get(rSocket.SocketID());
	if(session)
	{
		// ���ܴ��� 
		static char msgEnBuffer[65536];
		static char msgUnBuffer[65536];

		int nCHeadSize = sizeof(NetMsgC);
		int nSHeadSize = sizeof(NetMsgSS);
		memcpy(&msgEnBuffer[0], pMsg, nSize);		
		
		zEncrypt::xorCode(nSize, session->encrypt, msgEnBuffer, nSize);

		// ��װΪNetMsgSSͷЭ�飬�м䲹����ͷЭ����ֽڲ� 
		memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
		memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
		memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], nSize - nCHeadSize);

		pMsg = (NetMsgSS*)&msgUnBuffer[0];

		const MsgFunc* handler = GetMsgHandler(pMsg->protocol);
		if(handler == NULL)
		{
			H::logger->error("[���]�Ҳ���Э��:%d,��С:%d", pMsg->protocol,nSize);
			rSocket.OnEventColse();
			return;
		}
		else
		{
			H::logger->info("[���]�յ�Э��:%d", pMsg->protocol);
			(handler->handlerFun)(session, (PbMsgWebSS*)pMsg ,nSize + nSHeadSize - nCHeadSize);
		}
	}
	else
	{
		H::logger->error("[���]�Ҳ���������:%lld", rSocket.SocketID());
		rSocket.OnEventColse();
	}
}

void PlayerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	// ��ӡ�˳�ԭ��  
	H::logger->error("[���]���ӶϿ�:%lld", rSocket.SocketID());

	zSession* session = GameService::getMe().SessionMgr()->get(rSocket.SocketID());
	ASSERT(session);

	// �������δ������֤�����Բ�����WS�� 
	if (session->status < E_CLIENT_STATUS_ENCRYPTED)
	{
		return;
	}
}

// ���͵� ls 
void PlayerMsgHandler::ReqSendToLoginServer(zSession* pSession, const NetMsgSS* pMsg,int32_t nSize)
{
	if(pSession->status != E_CLIENT_STATUS_NOTIFY_INITED)
	{
		H::logger->warn("[���]�޷�ת����LS,����%lld״̬δ��ɳ�ʼ��", pSession->GetID());
		return;
	}
	zSession* ls = GameService::getMe().SessionMgr()->getLs();
	if (ls == NULL)
	{
		H::logger->warn("[���]�޷�ת����LS,�Ҳ���LS Session");
		return;
	}
	
	MSG_MAKE_PLAYER_SESSID(pSession->GetID(),GameService::getMe().GetServerID(),pMsg,nSize);
	ls->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

// ���͵� ss
void PlayerMsgHandler::ReqSendToSceneServer(zSession* pSession, const NetMsgSS* pMsg,int32_t nSize)
{
	if(pSession->status != E_CLIENT_STATUS_IN_SCENE)
	{
		H::logger->warn("[���]�޷�ת����SS,����%lld״̬δ���볡��", pSession->GetID());
		return;
	}

	GateUser* gateUser = GateUserManager::getMe().getBySessID(pSession->GetID());
	if (gateUser)
	{
		zSession* ss = GameService::getMe().SessionMgr()->getSs(gateUser->GetSceneServerID());
		if (ss == NULL)
		{
			H::logger->warn("[���]�޷�ת����SS,�Ҳ���SS,serverid:%d", gateUser->GetSceneServerID());
			return;
		}
		MSG_MAKE_PLAYER_SESSID(pSession->GetID(), GameService::getMe().GetServerID(), pMsg, nSize);
		ss->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
	}
}

// ���͵� ws
void PlayerMsgHandler::ReqSendToWorldServer(zSession* pSession, const NetMsgSS* pMsg,int32_t nSize)
{
	if(pSession->status <= E_CLIENT_STATUS_ENCRYPTED)
	{
		H::logger->warn("[���]�޷�ת����WS,����%lld״̬δ��ɳ�ʼ��", pSession->GetID());
		return;
	}
	zSession* ws = GameService::getMe().SessionMgr()->getWs();
	if (!ws)
	{
		H::logger->warn("[���]�޷�ת����WS,�Ҳ���WS Session");
		return;
	}
	MSG_MAKE_PLAYER_SESSID(pSession->GetID(), GameService::getMe().GetServerID(), pMsg, nSize);
	ws->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

void PlayerMsgHandler::SendToPlayer(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	static char arrUnBuffer[65536];
	static char arrEnBuffer[65536];
	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	int nCSize = nSize - (nSHeadSize - nCHeadSize);
	memcpy(&arrUnBuffer[0], pMsg, nSize);
	memcpy(&arrEnBuffer[0], &arrUnBuffer[0], nCHeadSize);
	memcpy(&arrEnBuffer[nCHeadSize], &arrUnBuffer[nSHeadSize], nSize - nSHeadSize);
	zEncrypt::xorCode(nCSize, pSession->encrypt, arrEnBuffer, nCSize);
	pSession->socket->ParkMsg((uint8_t*)&arrEnBuffer[0], nCSize);
}

void PlayerMsgHandler::ReqFepEncyptHandler(zSession* pSession,const NetMsgSS* pMsg,int32_t nSize)
{
	//if(pSession->status == E_CLIENT_STATUS_CONNECTED )
	//{
	//	char arrRandKey[MAX_ENCRYPTSIZE + 1];
	//	bzero(arrRandKey,sizeof(arrRandKey));
	//	zEncrypt::getRandKey(arrRandKey,MAX_NAMESIZE);
	//	
	//	C::RtEncryptInfo sendEncrypt;
	//	strncpy(sendEncrypt.encryptKey, arrRandKey, MAX_ENCRYPTSIZE);
	//	SendToPlayer(pSession, &sendEncrypt, sizeof(sendEncrypt));

	//	// Ҫ�ȷ����ݺ���ܸ� 
	//	strncpy(pSession->encrypt,arrRandKey,MAX_ENCRYPTSIZE);
	//	pSession->status = E_CLIENT_STATUS_ENCRYPTED;

	//	// ��÷�����״̬�Ƿ���� 
	//	S::SSRqCheckSerivces sendCheckSerivces;
	//	sendCheckSerivces.clientSessID = pSession->GetID();
	//	zSession* wsSession = GameService::getMe().SessionMgr()->getWs();
	//	if (!wsSession)
	//	{
	//		H::logger->warn("[���]��¼ǰ����������״̬�Ƿ����ת��ʧ�ܣ��Ҳ���WS Session");
	//		return;
	//	}
	//	wsSession->sendMsg(&sendCheckSerivces, sizeof(sendCheckSerivces));

	//	pSession->status = E_CLIENT_STATUS_NOTIFY_INITED;
	//}
	//else
	//{
	//	H::logger->error("[���]����%lld״̬δ���ӳɹ����޷������Կ", pSession->GetID());
	//}
}


