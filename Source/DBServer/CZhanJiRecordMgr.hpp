#ifndef __ZHAN_JI_MGR_H_
#define __ZHAN_JI_MGR_H_

#include <boost/pool/object_pool.hpp>

#include "SrvEngine.h"
#include "CZhanJiRecord.hpp"

/*
	��ս��ϵͳ������
	��¼���һ�����ڵ�ÿһ����������ϸ����������طŹ��ܵ�
*/

class CZhanJiRecordMgr : public zEntryMgr< zEntryID<0> >, public Singleton<CZhanJiRecordMgr>
{
public:
	CZhanJiRecordMgr() {};
	~CZhanJiRecordMgr() {};

	void LoadRecords();
	void UnSerialize(const fogs::proto::msg::QueryHistoryResponse proto);

	/*
	 * ������ʷ��¼
	 * recond_id ��¼�ţ�Ψһ
	 * innRecord ������Ϸ������ݣ�ÿ����ҵ���λ�š��ơ����֡����������ơ������ƣ��طż�¼��
	 * roomInfo ������Ϣ(����ӵ�һ��ʱӦ�ø�ֵ����������)
	 * roleInfo ��ɫ�б�(����ӵ�һ��ʱӦ�ø�ֵ����������)
	 * time ������Ϸʱ��(����ӵ�һ��ʱӦ�ø�ֵ����������)
	 */
	void AddRecord(uint64_t recond_id, const ::msg_maj::InnRecordS& innRecord,const ::msg_maj::InnReplayActionS& innReplay, uint32_t room_id = 0 ,const ::msg_maj::RoomInfo* roomInfo = NULL,const ::msg_maj::RoleInfoListS* roleInfo = NULL,uint64_t time = 0);

	/*
	 * ��ɼ�¼�������м���
	 * 1���������о֣���������
	 * 2�����겿�־֣������ɢ
	 * 3������ԭ�򣬷��䱻�ͷ�
	 */
	void FinishRecord(uint64_t record_id);

	template <class YourUserEntry>
	inline bool execEveryRecord(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr< zEntryID<0> >::execEveryEntry<>(exec);
	}

	void SendZhanjiReply(zSession* pSession, const fogs::proto::msg::ZhanjiQueryReply& proto);

public:

	bool GetByID(CZhanJiRecord* &entry,uint64_t nRecordID);
	bool GetByUID(std::vector<CZhanJiRecord*>& vecEntry, uint64_t uid);//
	bool GetByUIDRecordID(CZhanJiRecord* &entry, uint64_t uid, uint64_t nRecordID);

private:
	// 
	void AddRecord(const ::msg_maj::HistoryRecordS& record);
	bool AddRecord(CZhanJiRecord *obj);
	bool CheckAndRelease(CZhanJiRecord *obj); // ���Ƴ��ڴ棬���������ݿ�

	void AddUidRecordMap(uint64_t insertUID, CZhanJiRecord* obj);

private:

	std::map<uint64_t, std::map<uint64_t, CZhanJiRecord* > >  mapUidRecords;

	::boost::object_pool<CZhanJiRecord> objpoolZhanJi;
};



#endif