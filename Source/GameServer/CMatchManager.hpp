#ifndef __SORTS_MANAGER_H_
#define __SORTS_MANAGER_H_

#include "CMatchTemplate.hpp"
#include "FogsTimerService.hpp"

class CPlayer;
class zTaskTimer;


/* ���а����ݱ� */
enum MySortItem
{
	SORT_ITEM_WINS = 1,
	SORT_ITEM_SCORE = 2,
	SORT_ITEM_MAX,
};

// ����Key����
template<typename TKey>
struct SortKey
{
	uint64_t uid;		//��ɫID
	std::string name;	//����
	int32_t value;		//��
	time_t time;		//ʱ��
	int32_t sort;		//����
	int32_t type;		//�ڼ���
	SortKey()
	{
		uid = value = sort = time = type = 0;
	}
	virtual bool Compare(const TKey& key) const = 0;
	virtual bool operator==(const TKey& ar) const = 0;
};

//-------------------------��ʤ����key/value����-----------------------------------
// 2��8�ֳ�
struct Sort2r8jKey : public SortKey<Sort2r8jKey>
{
	virtual bool Compare(const Sort2r8jKey& _key) const
	{
		if (this->value > _key.value)
		{
			return true;
		}
		else if (this->value == _key.value)
		{
			return this->time < _key.time;
		}
		else
		{
			return false;
		}
	}
	virtual bool operator==(const Sort2r8jKey& ar) const
	{
		return this->uid == ar.uid;
	}
};

struct Sort2r8jValue : public Sort2r8jKey
{
	Sort2r8jValue(const Sort2r8jKey& key)
	{	
		uid = key.uid;
		name = key.name;
		value = key.value;
		time = key.time;
		sort = key.sort;
		type = key.type;
	}
	std::string actor_addr;

	int32_t roomID;
};

//-----------------------��������key/value����-----------------------------------
// 4��8�ֳ�
struct Sort4r8jKey : public SortKey<Sort4r8jKey>
{
	virtual bool Compare(const Sort4r8jKey& _key) const
	{
		if (this->value > _key.value)
		{
			return true;
		}
		else if (this->value == _key.value)
		{
			return this->time < _key.time;
		}
		else
		{
			return false;
		}
	}

	virtual bool operator==(const Sort4r8jKey& ar) const
	{
		return this->uid == ar.uid;
	}
};

struct Sort4r8jValue : public Sort4r8jKey
{
	Sort4r8jValue(const Sort4r8jKey& key)
	{
		uid = key.uid;
		name = key.name;
		value = key.value;
		time = key.time;
		sort = key.sort;
		type = key.type;
	}
	std::string actor_addr;
};

//------------------------------------------------------------

class CMatchManager : public Singleton<CMatchManager>
{
public:
	CMatchManager();
	~CMatchManager();

	void Init();

	void loadDB();
	void SaveAllSorts();

	void Serialize(fogs::proto::msg::QuerySaveRanks& proto);
	void UnSerialize(const fogs::proto::msg::QuerySaveRanks& proto);

	// ��ʱ�ص�����
	void Timer();

	void SendTopList(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void GetMyTopList(uint64_t nCharID, ::msg_maj::rank_type rankType, std::pair<int32_t, int32_t>& myRankScore);

	void Update(const Sort2r8jKey& key, const Sort2r8jValue& value);
	void Update(const Sort4r8jKey& key, const Sort4r8jValue& value);

	void SaveWinsSort();
	void SaveScoreSort();

	// ��¼���䣬ȥ��������
	int32_t GetMyMacthID(uint64_t userID) const;

private:

	fogs::FogsTimer*	m_pTimer;

	CMatchTemplate<Sort2r8jKey, Sort2r8jValue> sort2r8jTaotai;	// 2r8j��̭��
	CMatchTemplate<Sort4r8jKey, Sort4r8jValue> sort2r8jZhifen;	// 2r8j������
};

#endif