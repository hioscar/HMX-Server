#ifndef _CMA_JIANG_H_
#define _CMA_JIANG_H_
#include <boost/pool/object_pool.hpp>

#include "CMajingRule.hpp"

struct stSeatEvent
{
	::msg_maj::event_type etype;	//�¼�����
	uint16_t usSeat;				//��λ
	bool bAction;					//����

	stSeatEvent()
	{
		etype = ::msg_maj::e_none;
		usSeat = 0;
		bAction = false;
	}
};
typedef std::vector<stSeatEvent> vecSeatEvent;

enum eActionType
{
	eActionType_NULL		= 0, //��
	eActionType_SendCard	= 1, //����
	eActionType_Discard		= 2, //����
};

class CRoom;

class CMaJiang
{
public:
	CMaJiang(CRoom* pRoom);
	~CMaJiang();

	inline void SetRule(CMajingRule* pRule) { m_pRule = pRule; }

	void Release();

	bool InitMajing();

	void InitMaPai();

	void OpenMaPai();

	void OpenYiMaAllHit();

	void GMSetMajiang(const std::vector<uint16_t>& pailist);

	void GMSetPai(uint16_t usPai);

	uint16_t GetPai();

	inline const std::vector<uint16_t>& GetRemainPaiList() { return m_vecPaiList; }

	inline bool CheckHasPai() const { return GetRemainPaiNum() > 0; }

	inline uint16_t GetRemainPaiNum() const { return m_vecPaiList.size() - m_usMaPaiNum; }

	void InitPai();

	void GetFilterPai(std::vector<uint16_t>& vevFilter);

	void GetMaxCardTypeNum(uint16_t usSeat, eCardType& etype, uint16_t& usNum);

	void ChangePai(uint16_t usSeat, std::vector<uint16_t>& changelist);

	bool ChangePaiEx(uint16_t usSeat, std::vector<uint16_t>& pailist);

	void RandomRoll();

	uint32_t GetRandRoll() const;

	bool GMOper();

	bool InitFanGhostPai();

	void AddSeatEvent(::msg_maj::event_type etype, uint16_t usSeat, bool bAction = false);

	uint16_t GetEventSeatNum();

	bool DelSeatEvent(uint16_t usSeat);

	bool CheckEvent(::msg_maj::event_type etype, uint16_t usSeat);

	bool DoSeatEvent(::msg_maj::event_type etype, uint16_t usSeat);

	bool IsDoAllSeatEvent() const;

	const vecSeatEvent& GetEventList() { return m_vecSeatEvent; }

	void AddHuPai(const stHuPai& st);

	void GetHuPai(uint16_t usPos, stHuPai& hupai) const;

	void DelHuPai(uint16_t usSeat);

	inline void ClearHuPai() { m_vecHuPai.clear(); }

	::msg_maj::hu_way GetHuWay() const;

	void GetActionEvent(stSeatEvent& st) const;

	::msg_maj::event_type GetEventTypeBySeat(uint16_t usSeat) const;

	bool IsHasHuEvent() const;

	inline bool IsHasEvent() { return m_vecSeatEvent.size() > 0; }

	inline uint16_t GetCurPos() const { return m_curMJPos; }
	inline uint16_t GetMaxPos() const { return m_maxMjPos; }

	inline uint16_t GetUsCurActionPos() const { return m_usCurActionPos; }

	inline uint16_t GetMaPaiNum() const { return m_usMaPaiNum; }
	inline const ::vector<uint16_t>& GetMaPaiList() const { return m_vecMaPai; }

	inline vecHuPai& GetVecHuPai() { return m_vecHuPai;}
	inline uint16_t GetHuPaiSize() const { return m_vecHuPai.size(); }
	inline const stHuPai& GetHuPaiFirst() { return m_vecHuPai[0]; }
	inline bool IsNotHued() const { return m_vecHuPai.empty(); }
	void DeleteHuPaiExtOne(uint16_t nSeat);

	inline void SetLoopPoses(uint16_t nLoopPos) { m_nLoopPoses = nLoopPos; }
	inline uint16_t GetLoopPoses() const { return m_nLoopPoses; }
	inline void SetLoopEvents(uint16_t nLoopEvent) { m_nLoopEvents = nLoopEvent; }
	inline uint16_t GetLoopEvents() const { return m_nLoopEvents; }
	inline void AddDiscards(uint16_t usPai) { m_vecDiscards.push_back(usPai); }
	inline const std::vector<uint16_t>& GetDiscards() const { return m_vecDiscards; }
	inline const vecLastHuInfo& GetLastHuSeat() const { return m_vecLastHuInfo; }
	uint16_t GetLastHuPaiTimes(uint16_t seat); // ������������� 
	uint16_t GetLastBankerTimes(uint16_t seat);
	inline uint16_t GetFanPai() const { return m_nFanPai; }

	inline uint16_t GetYiMaAllHitPai() const { return m_usYiMaAllHit; }

	inline uint16_t GetSendCardPos() const { return m_usSendCardPos; }
	void SetSendCardPos(uint16_t usPos);
	bool HasThisEventTypeBySeat(uint16_t usSeat, ::msg_maj::event_type etype) const;
	void AddOutPai(uint16_t usPai, uint16_t usNum);
	void CheckLastPai(uint16_t usPai, const std::vector<uint16_t>& vecPaiList, const vecEventPai& eventList, std::pair<uint16_t, uint16_t>& o_lastPaiPair);

private:

	// GMc����ʹ��
	bool m_bGM;
	std::vector<uint16_t> m_vecGMPailist;

	CRoom* m_pRoom; //��������
	CMajingRule* m_pRule;

	std::vector<uint16_t> m_vecPaiList; //���е���

	uint16_t m_curMJPos; //��ǰ����λ��(��)

	uint16_t m_maxMjPos;// ����λ��

	uint16_t m_usMaPaiNum; //��������

	std::vector<uint16_t> m_vecMaPai;	//��������
	uint16_t m_usYiMaAllHit;			//һ��ȫ��
	vecHuPai m_vecHuPai;				//��������

public:

	uint32_t m_unRoll; //����

	uint16_t m_usSendCardPos;	//�ֵ����Ƶ�λ��

	uint16_t m_usSendCardNum;	//���Ƶ�����

	uint16_t m_usDicardPos;		//�ֵ����Ƶ�λ��

	eActionType m_eActionType; //��������

	uint16_t m_usCurActionPos;	//����λ��

	uint16_t m_usCurActionPai;	//��ǰ��/�����

	vecSeatEvent m_vecSeatEvent; //���ʹ����¼��������ͻ��˲�����֤

	bool m_bActionEvent;		//�Ƿ�����¼�

	uint16_t m_usGang;			//������ 0:�� 1:���� 2:���� 3:���ָ� 

	// һ�ڶ��죬�ж������
	uint16_t m_nLoopPoses;		//���ƴ�����¼
	uint16_t m_nLoopEvents;		//�¼�������¼(���˹�)

	// ��ׯ����
	bool m_bHadCheckGZ;				
	bool m_bGenZhuangSuccess;		//��ׯ�Ƿ�ɹ�
	std::vector<uint16_t> m_vecDiscards; // ������Ƽ�¼

	// ��̬����
	bool m_bHadFan;
	bool m_bHadSendGhost;
	uint16_t m_nFanPai;

	// ��������
	vecLastHuInfo m_vecLastHuInfo;

	// ��ׯ����
	stLastBanker m_stLastBanker;

	// ��һ�θܵ���
	uint16_t m_nLastGangType;
	uint16_t m_nLastGangPai;
	uint16_t m_nLastGangPos;
	uint16_t m_nLastGangFromPos;

	// ��һ��������
	uint16_t m_nLastPengPai;
	uint16_t m_nLastPengFromPos;

	// ��һ������λ��
	int16_t m_usFirstSeat;

	bool m_bEnd;				//���ֽ���

	std::map<uint16_t, uint16_t> m_mapOutPai;// ��������ϵ��ƣ�����������������ܡ����ܡ�����

};

extern ::boost::object_pool<CMaJiang> g_objpoolMaJiang;

#endif // !_CMA_JIANG_H_
