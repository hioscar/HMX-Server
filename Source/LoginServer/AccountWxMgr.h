#ifndef __ACCOUNT_MGR_H_
#define __ACCOUNT_MGR_H_

#include "SrvEngine.h"
#include "AccountWx.h"

#include <boost/pool/object_pool.hpp>

/*
	΢��Token�����Զ������ˢ��access_token����Чֵ
 */

class AccountWx;

class AccountWxMgr : protected zEntryMgr< zEntryID<0>, zEntryName > 
{
public:
	AccountWxMgr();
	~AccountWxMgr();

	void LoginAccountWx(const ::data::AccountWxInfo& data);

	void Timer();

private:

	std::map<std::string, AccountWx>	m_mapAccountWx;
	::boost::object_pool<AccountWx>		objpool;

};

#endif

