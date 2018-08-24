#ifndef __SORTS_MANAGER_H_
#define __SORTS_MANAGER_H_

#include "CSortTemplate.hpp"
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
	uint64_t uid;
	std::string name;
	int32_t value;
	time_t time;
	int32_t sort;
	int32_t type;
	SortKey()
	{
		uid = value = sort = time = type = 0;
	}
	virtual bool Compare(const TKey& key) const = 0;
	virtual bool operator==(const TKey& ar) const = 0;
};

//-------------------------��ʤ����key/value����-----------------------------------

struct SortWinsKey : public SortKey<SortWinsKey>
{
	virtual bool Compare(const SortWinsKey& _key) const
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
	virtual bool operator==(const SortWinsKey& ar) const
	{
		return this->uid == ar.uid;
	}
};

struct SortWinsValue : public SortWinsKey
{
	SortWinsValue(const SortWinsKey& key)
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

//-----------------------��������key/value����-----------------------------------

struct SortScoreKey : public SortKey<SortScoreKey>
{
	virtual bool Compare(const SortScoreKey& _key) const
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

	virtual bool operator==(const SortScoreKey& ar) const
	{
		return this->uid == ar.uid;
	}
};

struct SortScoreValue : public SortScoreKey
{
	SortScoreValue(const SortScoreKey& key)
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

class CSortsManager : public Singleton<CSortsManager>
{
public:
	CSortsManager();
	~CSortsManager();

	void Init();

	void loadDB();
	void SaveAllSorts();

	void Serialize(fogs::proto::msg::QuerySaveRanks& proto);
	void UnSerialize(const fogs::proto::msg::QuerySaveRanks& proto);

	// ��ʱ�ص�����
	void Timer();

	void SendTopList(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void GetMyTopList(uint64_t nCharID, ::msg_maj::rank_type rankType, std::pair<int32_t, int32_t>& myRankScore);

	void Update(const SortWinsKey& key, const SortWinsValue& value);
	void Update(const SortScoreKey& key, const SortScoreValue& value);

	void SaveWinsSort();
	void SaveScoreSort();

private:
	fogs::FogsTimer*	m_pTimer;
	uint64_t			m_lastTurnYmd; // �ϴεķ�תʱ�� 

	CSortTemplate<SortWinsKey, SortWinsValue> sortTempWins;		// ��ʤ���а�
	CSortTemplate<SortScoreKey, SortScoreValue> sortTempScore;	// �������а�
};

#endif