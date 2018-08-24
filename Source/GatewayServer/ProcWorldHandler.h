#ifndef _PROC_WORLD_HANDLER_H_
#define _PROC_WORLD_HANDLER_H_

#include "SrvEngine.h"
#include "Single.h"

struct NetMsgSS;

/*-------------------------------------------------------------------
 * @Brief :FEP��Ϊ�ͻ��ˣ�������WS�߼�����Handler 
 * 
 * @Author:hzd 2013/04/03
 *------------------------------------------------------------------*/
class ProcWorldHandler : public Single<ProcWorldHandler>
{
public:
	ProcWorldHandler();
	~ProcWorldHandler();

	void ReqLogin(zSession* pBaseSession, const NetMsgSS* pMsg,int32_t nSize);
};


#endif

