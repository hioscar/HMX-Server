#ifndef _LOGIN_TOKEN_H_
#define _LOGIN_TOKEN_H_

#include "SrvEngine.h"
#include "Single.h"

// ��¼����ʱ���棬��Ҫ���ڸ���΢���û�һЩ�䶯����Ϣ

class LoginTokenMgr : public Single<LoginTokenMgr>
{
public:
	LoginTokenMgr();
	~LoginTokenMgr();
	void AddToken(const ::msg_maj::LoginToken& loginToken);
	const ::msg_maj::LoginToken* GetToken(const std::string& unionid);
private:

	std::map<std::string, ::msg_maj::LoginToken> m_mapLoginToken;
};

#endif

