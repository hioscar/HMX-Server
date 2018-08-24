#ifndef _CCACHE_MAIL_MGR_H_
#define _CCACHE_MAIL_MGR_H_

#include <boost/pool/object_pool.hpp>
#include "SrvEngine.h"

// ������ʱ����ʱ��(��)

const int64_t g_unModifyDelayTime = 60;	// �����Ӻ�ʱ����
const int64_t g_unOfflineDelayTime = 600; // �ڴ���������ʱ��,��ֵҪ����g_unModifyDelayTime

class CCacheMail;

/*
 *
 * �ʼ����������(uid)
 *
 */
class CCacheMailMgr : public zEntryMgr< zEntryID<0> >, public Singleton<CCacheMailMgr>
{
public:
	CCacheMailMgr();
	~CCacheMailMgr();

	bool AddMail(CCacheMail* mail);
	CCacheMail* GetByID(uint64_t id);
	void RemoveMail(CCacheMail* mail);

	bool GetByUid(uint64_t uid,std::vector<CCacheMail*>& vecMail);
	void AddQuery(uint64_t uid);
	void AddModify(uint64_t id);
	void AddOffline(uint64_t id);

	void CheckModify();
	void CheckOffline();

private:

	std::map<uint64_t, std::map<uint64_t, CCacheMail*, std::greater<uint64_t> > > mapUidRecords;
	std::set<uint64_t> setUidQuery; // �Ƿ��ѯ

	std::map<uint64_t,time_t> m_mapModifys;	// �и��µ��ʼ�
	std::map<uint64_t,time_t> m_mapOfflines;// ���ߵ��ʼ�

};

extern ::boost::object_pool<CCacheMail> g_objpoolCacheMail;

#endif // !_CCACHE_MAIL_MGR_H_


