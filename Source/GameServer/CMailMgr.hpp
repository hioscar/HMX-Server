#ifndef _CMAIL_MGR_H_
#define _CMAIL_MGR_H_

#include "Global.hpp"
#include "SrvEngine.h"
#include "CMail.hpp"

/*

	�ʼ�������

 */

class CMailMgr : public zEntryMgr< zEntryID<0> > , public Single< CMailMgr >
{
public:
	CMailMgr();
	~CMailMgr();
	void OnSystemStart();
	void OnlinePlayer(uint64_t uid);
	void OfflinePlayer(uint64_t uid);
	void UnSerialize(const ::fogs::proto::msg::QueryMailResponse proto);

	/*
	 * ��ĳ�˷��ʼ�
	 * toPlayer ���
	 * title ����
	 * content ����
	 * room_cards �Ƿ�������
	 */
	bool SendToPlayer(const CPlayer& toPlayer, const std::string& title, const std::string& content, int32_t room_cards);

	/*
	 * ��һЩ�˷��ʼ�
	 * toPlayer ���
	 * title ����
	 * content ����
	 * room_cards �Ƿ�������
	 */
	void SeendToPlayers(const std::vector<const CPlayer*> &vecPlayer, const std::string& title, const std::string& content, int32_t room_cards);

	/*
	 * ��ĳ�˷��ʼ�
	 * fromID ������,0Ϊϵͳ
	 * fromName ����������, ""Ϊϵͳ
	 * toUid �ռ���ID
	 * toName �ռ�������
	 * title ����
	 * content ����
	 * room_cards �Ƿ�������
	*/
	bool SendToPlayer(uint64_t fromID, const std::string& fromName, uint64_t toUid, const std::string& toName, const std::string& title, const std::string& content, int32_t room_cards);

	template <class YourUserEntry>
	inline bool execEveryMail(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr< zEntryID<0> >::execEveryEntry<>(exec);
	}

	bool GetByID(CMail* &entry, int64_t nMailID);
	bool GetSys(std::vector<CMail*>& vecEntry,uint64_t uid);
	bool GetByUID(std::vector<CMail*>& vecEntry, uint64_t uid,uint64_t start_index = 0,int32_t num = 50);
	bool GetByUIDMailID(CMail* &entry, uint64_t uid, uint64_t nMailID);

	void SendMailList(CPlayer* pPlayer,int32_t start_index = 0);

	void TestAdd(const std::string& account);
	void TestModify();

	void AddRecord(const ::msg_maj::MailRecordS& record, bool isNew);

private:

	bool AddRecord(CMail *obj);
	bool CheckAndRelease(CMail *obj,bool isRelease = false); // ���Ƴ��ڴ棬���������ݿ�
	void Release(CMail *obj);
	void Recond2ProtoC(uint64_t uid,const CMail& mail, ::msg_maj::MailRecordC& distProto);

private:
	uint64_t m_unMaxID; // ����ID 
	std::map<uint64_t, CMail*, std::greater<uint64_t> >							mapSysRecords;	// ϵͳ�ʼ�(ID=>����)
	std::map<uint64_t,std::map<uint64_t,CMail*,std::greater<uint64_t> > >		mapUidRecords;	// �����ʼ�(uid=>ID=>����)
};


//----------------------------------------------------
// ϵͳ�����ʼ�
class CMailSysLogMgr : public zEntryMgr< zEntryID<0> >, public Single< CMailSysLogMgr >
{
public:
	CMailSysLogMgr();
	~CMailSysLogMgr();
	void OnlinePlayer(uint64_t uid);
	void OfflinePlayer(uint64_t uid);
	void UnSerialize(const ::fogs::proto::msg::QueryMailSystemLogResponse proto);
	CMailSysLog* GetByID(int64_t nMailID);
	bool GetByUID(std::vector<CMailSysLog*>& vecEntry, uint64_t uid, uint64_t start_index = 0, int32_t num = 50);
	CMailSysLog* GetByUIDMailID(uint64_t uid,uint64_t mail_id);
	void Release(CMailSysLog *obj);
	CMailSysLog* AddRecord(const ::msg_maj::MailSystemLogS& record, bool isNew);

private:
	bool AddRecord(CMailSysLog *obj);
private:
	std::map<uint64_t, std::map<uint64_t, CMailSysLog*, std::greater<uint64_t> > >	mapUidRecords;	// �����ʼ�(uid=>ID=>����)
};

#endif


