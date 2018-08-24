#include "NetMsgHandler.h"
#include "PlayerProcHandler.h"
#include "GameService.h"
#include "Player.h"
#include "PlayerMgr.h"

NetMsgHandler::NetMsgHandler():zMsgHandler(GameService::Instance())
{
	/* common ��Ҫ�õ��ڲ�Э�� */
	/* �ڲ�Э�飬�����ֲ�ͬservertype����ȥ��ͳһ�����飬���¼�������б�ping�ȵȲ��� */
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
	}

#undef REGISTER_INTERNAL_MESSAGE

	// from server
#define REGISTER_FEP_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerProcHandler::handler, PlayerProcHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_FEP_MESSAGE

}


NetMsgHandler::~NetMsgHandler()
{
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("���ӳɹ���������:id=%d ip=%s,port=%d", rSocket.SocketID(), rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());
	zSession* pSession = GameService::getMe().SessionMgr()->get(rSocket.SocketID());
	if (pSession)
	{
		Player* player = PlayerMgr::getMe().get(pSession->GetID());
		if (player)
		{
			PlayerProcHandler::SendEncrypt(player);
			H::logger->info("����������Կ��Ϣ��:ip=%s port=%d", rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());
		}
	}
	else
	{
		ASSERT(0);
	}
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize)
{
	zSession* pSession = GameService::getMe().SessionMgr()->get(rSocket.SocketID());
	if (pSession == NULL)
	{
		H::logger->error("Can not find session");
		rSocket.OnEventColse();
		return;
	}

	// ���ܴ��� 
	static char msgEnBuffer[65536];
	static char msgUnBuffer[65536];

	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	memcpy(&msgEnBuffer[0], pMsg, nSize);

	zEncrypt::xorCode(nSize, pSession->encrypt, msgEnBuffer, nSize);

	// ��װΪNetMsgSSͷЭ�飬�м䲹����ͷЭ����ֽڲ� 
	memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
	memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
	memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], nSize - nCHeadSize);

	pMsg = (NetMsgSS*)&msgUnBuffer[0];

	const MsgFunc* pMsgHandlerInfo = GetMsgHandler(pMsg->protocol);
	if (pMsgHandlerInfo == NULL)
	{
		H::logger->error("�Ҳ�����Э��:%d,��С:%d", pMsg->protocol, nSize);
		rSocket.OnEventColse();
		return;
	}

	H::logger->info("�յ�Э��=%d", pMsg->protocol);

	(pMsgHandlerInfo->handlerFun)((zSession*)(pSession), (PbMsgWebSS*)pMsg, nSize);
}

/* ��Server�Ͽ��ص�(��ʱsocket�Ѿ�����) */
void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	H::logger->info("���ӶϿ���������:id=%d ip=%s,port=%d", rSocket.SocketID(), rSocket.GetIp().c_str(), (int32_t)rSocket.GetPort());
}










