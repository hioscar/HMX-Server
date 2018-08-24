#include "SrvEngine.h"
#include <boost/pool/object_pool.hpp>
#include "CRobot.hpp"

class CConnection;

struct stSound
{
	stSound(const std::string _path, int _normal_man, int _normal_women, int _fy_man, int _fy_women)
	{
		path = _path;
		normal_man = _normal_man;
		normal_women = _normal_women;
		fy_man = _fy_man;
		fy_women = _fy_women;
		msg_index = 0;
	}
	std::string path; // : "tiao_1",
	int normal_man;
	int normal_women;
	int fy_man;
	int fy_women;
	int msg_index;
};

class CRobotMgr : public zEntryMgr< zEntryID<0> > , public Singleton<CRobotMgr>
{
public:
	CRobotMgr();
	~CRobotMgr();

	void InitSound();
	int32_t GetOutCardSound(CRobot* robot, int16_t type, int16_t point);
	int32_t GetStateSound(CRobot* robot, ::msg_maj::event_type state);
	int32_t GetOutCardSoundIndex(CRobot* robot, const stSound& sound);

	bool StartNewRobot(zSession* pSession,uint32_t sessionID,uint64_t uid);

	void StopRebot(uint64_t uid);

	CRobot* GetRobot(uint32_t unSessionID) const;

	CRobot* GetMaster(CRobot* entry);
	void GetFriends(CRobot* entry,std::vector<CRobot*>& vecFriend);

	template <class YourUserEntry>
	inline bool execEveryRobot(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr< zEntryID<0> >::execEveryEntry<>(exec);
	}

	std::string GetPaiZhong(uint16_t usPai);

	void OpenRoom();

	void CheckLoginAll();

	// ����Ƿ���ͬ���
	void CheckHasVerifyPai(const std::vector<uint16_t>& pailist);

	// ������֤��
	void AddVerifyPai(uint16_t num1, uint16_t num2, uint16_t num3, uint16_t num4, uint16_t num5, uint16_t num6, uint16_t num7, uint16_t num8, uint16_t num9);

	// ��ȡ�ﵽ����������б�
	void GetGroupPai(uint16_t usNum);

	// ��ȡ�ﵽ����������б�����
	void GetGroupPaiZi(uint16_t usNum);

	// ��������
	void GeneratePai(uint32_t usGhostNum);

	// �������ͣ�����
	void GeneratePai_Jiang(uint32_t usGhostNum);

	// ������������
	void GeneratePaiZi(uint32_t usGhostNum);

	// �����������ƣ�����
	void GeneratePaiZi_Jiang(uint32_t usGhostNum);

	// ��������
	void GeneratePai_ting(uint32_t usGhostNum);

	// ��������
	void GeneratePai_ting_Jiang(uint32_t usGhostNum);

public:

	CConnection* m_pGameConn;
	fogs::FogsTimer* m_pTimer_1_login;

	::boost::object_pool<CRobot> objpool;

	uint32_t m_nGoTimes;

	uint16_t m_usID;

	uint16_t m_usGhostNum;

	std::map<uint64_t, std::vector<uint16_t> > group_list;

	fogs::FogsTimer*  m_pTimer_verify;

	uint32_t m_unProductID;
	std::string m_strIP;
	uint16_t m_usPort;
	std::string m_strConnIP;
	uint16_t m_usConnPort;
	std::string m_strRobotName;
	uint16_t m_usRobotNum;

	std::map<std::string, stSound>	m_mapSoundData;
};