#ifndef __LOGIN_ACCOUNT_MGR_H_
#define __LOGIN_ACCOUNT_MGR_H_


#include "Single.h"
#include "SrvEngine.h"

/*------------------------------------------------------------------
 *
 * @Brief : �ʺŵ�¼������ʱʧЧ���������²�������
 *
 * @Author: hzd 
 * @File  : LoginAccountMgr.h
 * @Date  : 2015/10/19 23:21
 * @Copyright (c) 2015,hzd, All rights reserved.
 *-----------------------------------------------------------------*/

/*------------------------------------------------
 *  �ʺ���Ϣ
 *-----------------------------------------------*/
struct StAccountInfo
{

	int32_t nSessionID;
	int32_t nAccountId;
	char  arrName[MAX_ACCOUNT_LENG];
	int32_t nLastLogin;
	int32_t nIllegalTime;

	StAccountInfo(int32_t _nSessionID)
	{
		nSessionID = _nSessionID;
		nAccountId = nLastLogin = nIllegalTime = 0;
	}

	/*--------------------------------------------
	 *  @brief    :	��¼��¼
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void AddLoginTimes()
	{
		nIllegalTime++;
	}

	/*--------------------------------------------
	 *  @brief    :	�Ƿ�Ƿ�
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	bool CheckLoginIllegal()
	{
		if( nIllegalTime > 3 )
		{
			nIllegalTime = 0;
			return true;
		}
		return false;
	}
};


class LoginAccountMgr : public Single<LoginAccountMgr>
{
public:

	LoginAccountMgr(void);
	~LoginAccountMgr(void);

	/*--------------------------------------------
	 *  @brief    :	�������
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void Update(int32_t nServerTimes);

	/*--------------------------------------------
	 *  @brief    :	����ʺ���Ϣ
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* GetAccountInfo(int32_t nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	�����ʺż�¼
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* AddAccountInfo(int32_t nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	ɾ��һ���ʺż�¼
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RemoveAccountInfo(int32_t nFepSessionId);

private:

	typedef std::map<int32_t,StAccountInfo*> AccountInfoMapType;

	AccountInfoMapType m_mapAccountInfo;

	zObjPool<StAccountInfo> s_cAccountInfoFactory;

};

#endif



