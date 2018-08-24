#ifndef _SCENE_SERVER_MSG_HANDLER_H_
#define _SCENE_SERVER_MSG_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

size_t onFindBindInfo(void *buffer, size_t size, size_t nmemb, void *parm);
size_t onBindingAgent(void *buffer, size_t size, size_t nmemb, void *parm);
size_t onInputInviteCode(void *buffer, size_t size, size_t nmemb, void *parm);

class ProcSsHandler : public Single<ProcSsHandler>
{
public:
	ProcSsHandler();
	~ProcSsHandler();

	void TransTerToSceneReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void TransTerToSceneResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void NotifyUpdateRankInfo(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnQueryRankRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnAddRoomToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnUpdateRoomToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnRemoveRoomToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void OnSyncRoleToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnReqRobotJoinRoom(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnReqBindInfoReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnReqBindAgentReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnInputInviteCodeReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	/*--------------------------------------------
	 *  @brief    :	���󳡾�ע�ᣬ��ss��¼ws��ɺ�����ע���������ڵĵ�ͼID
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneRegister(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	/*--------------------------------------------
	 *  @brief    :	���󳡾�ע��������ȡ��������ͼע��
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneCancel(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	/*--------------------------------------------
	 *  @brief  : ���볡���󷵻صĽ�� 
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RpEnterSceneResult(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void RpChangeScene(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

};

#endif


