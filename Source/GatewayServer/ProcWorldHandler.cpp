#include "ProcWorldHandler.h"


ProcWorldHandler::ProcWorldHandler()
{
}


ProcWorldHandler::~ProcWorldHandler()
{
}


void ProcWorldHandler::ReqLogin(zSession* pSession, const NetMsgSS* pMsg,int32_t nSize)
{

	if(pSession->status != E_SERVER_STATUS_CONNETED)
	{
//		FLOG_INFO("pBaseSession->getStatus() != E_SERVER_STATUS_CONNETED");
		return;
	}

	// �ж� 
	pSession->status = E_SERVER_STATUS_LOGINED;

	// ok finish!
	// �ȴ����� ls,ss������  

}

