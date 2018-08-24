#ifndef _CMAIL_H_
#define _CMAIL_H_

#include <boost/pool/object_pool.hpp>

#include "Global.hpp"
#include "SrvEngine.h"

/*
 
	�����ʼ�:�ʼ�ID�����͡������ߡ������ߡ����⡢���ݡ���������ǡ�ʱ��

 */

class CPlayer;

class CMail : public zEntry
{
public:
	CMail(const ::msg_maj::MailRecordS& mail);
	~CMail();
	USE_IMP_ENTRY_GetID;
	USE_IMP_ENTRY_TempID;
	USE_IMP_ENTRY_GetName;
	inline uint64_t GetMailID() const { return m_unMailID; }
	inline ::msg_maj::mail_type GetType() const { return m_eType; }
	inline uint64_t GetFromID() const { return m_unFromID; }
	inline const std::string& GetFromName() const { return m_strFromName; };
	inline uint64_t GetToID() const { return m_unToID; }
	inline const std::string& GetToName() const { return m_strToName; }
	inline const std::string& GetTitle() const { return m_strTitle; }
	inline const std::string& GetContent() const { return m_strContent; }
	inline int32_t GetRoomCards() const { return m_nRoomCards; }
	inline ::msg_maj::mark_type GetMark() const { return m_eMark; }
	inline void SetMark(::msg_maj::mark_type _type) { m_eMark = _type; }
	inline time_t GetCreateTime() const { return m_nCreateTime; }
	inline void SetFetchTime(time_t _time) { m_nFetchTime = _time; }
	inline time_t GetFetchTime() const { return m_nFetchTime; }

	bool DoRead();
	bool DoFetchAward();
	bool DoDelete();

	void Save();

	bool IsExpire();
	
private:

	uint64_t&				m_unMailID;		// �ʼ�ID
	::msg_maj::mail_type   m_eType;		// ����
	uint64_t				m_unFromID;		// ������ID
	std::string				m_strFromName;	// ����������
	uint64_t				m_unToID;		// ������ID
	std::string				m_strToName;	// ����������
	std::string				m_strTitle;		// �ʼ�����
	std::string				m_strContent;	// �ʼ�����
	int32_t					m_nRoomCards;	// ��������
	::msg_maj::mark_type	m_eMark;		// �������
	time_t					m_nCreateTime;	// ����ʱ��
	time_t					m_nFetchTime;	// ��ȡʱ��
	time_t					m_expireTime;	// ����ʱ��
};

extern ::boost::object_pool<CMail> objpoolMail;


class CMailSysLog : public zEntry
{
public:
	CMailSysLog(const ::msg_maj::MailSystemLogS& mail);
	~CMailSysLog();
	//virtual inline uint64_t GetID() = 0;/* { return _entry_id; };*/
	virtual inline uint64_t GetTempID() { return _entry_tempid; }
	virtual inline const std::string& GetName() { return _entry_name; }
	virtual inline uint64_t GetID() { return m_unUnID; }
	inline uint64_t GetMailID() const { return m_unMailID; }
	inline uint64_t GetUID() const { return m_unUID; }
	inline ::msg_maj::mark_type GetMark() const { return m_eMark; }
	inline void SetMark(::msg_maj::mark_type _type) { m_eMark = _type; }
	inline time_t GetCreateTime() const { return m_nCreateTime; }
	inline void SetFetchTime(time_t _time) { m_nFetchTime = _time; }
	inline time_t GetFetchTime() const { return m_nFetchTime; }
	inline uint32_t GetRoomCards();

	bool DoRead();
	bool DoFetchAward();
	bool DoDelete();

	void Save();
	bool IsExpire();

private:

	uint64_t&				m_unUnID;		// ΨһID
	uint64_t				m_unMailID;		// �ʼ�ID
	uint64_t				m_unUID;		// ������ID
	::msg_maj::mark_type	m_eMark;		// �������
	time_t					m_nCreateTime;	// ����ʱ��
	time_t					m_nFetchTime;	// ��ȡʱ��
	time_t					m_expireTime;	// ����ʱ��
};

extern ::boost::object_pool<CMailSysLog> objpoolMailSysLog;

#endif

