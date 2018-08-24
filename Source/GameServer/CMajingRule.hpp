#ifndef __MAJIANG_RULE_H__
#define __MAJIANG_RULE_H__

#include "Global.hpp"
#include "GamePublic.h"
#include "MaJiangPublic.h"

class CRoom;
class CPlayer;
class CMaJiang;
enum eRoomStatus;

enum eWanFaMask
{
	WAN_FA_MASK_GHOST = 1,
	WAN_FA_MASK_DaHuJiaBei = 2,
	WAN_FA_MASK_CanPaoHu = 4,
	WAN_FA_MASK_GangShangPaoBao3Jia = 8,
	WAN_FA_MASK_QiangGangBao3Jia = 16,
	WAN_FA_MASK_GangKaiHuaBao3Jia = 32,
	WAN_FA_MASK_258ZuoJiang = 64,
	WAN_FA_MASK_258ZuoJiangJiaBei = 128,
	WAN_FA_MASK_Hu258JiaBei = 256,
	WAN_FA_MASK_QingYiSeJiaBei = 512,
	WAN_FA_MASK_WuGuiJiaBei = 1024,
	WAN_FA_MASK_DaHuDianPao = 2048,
	// �淨 1:�޹����,2:����ӷ�,4:�ɽ��ں�,8:�ɸ����� 16���ܰ����� 32���ϻ�������,64:258����,128:258�����ӷ�,256:��258�ӷ�,512:��һɫ�ӷ�,1024:�޹�ӷ�,2048:����ɵ���
};

struct stHuPai
{
	::msg_maj::hu_type m_eHupaiType;	//��������
	::msg_maj::hu_way m_eHupaiWay;		//���Ʒ�ʽ
	uint16_t m_usHupaiPos;				//����λ��
	uint16_t m_usMulti;					//���Ʊ���
	uint16_t m_usPai;					//������
	stHuPai()
	{
		m_eHupaiType = ::msg_maj::hu_none;
		m_eHupaiWay = ::msg_maj::hu_way_none;
		m_usHupaiPos = m_usMulti = m_usPai = 0;
	}
	::msg_maj::hu_way getDefHuWay() const
	{
		return (::msg_maj::hu_way)(m_eHupaiWay % 10);
	}
};
typedef std::vector<stHuPai> vecHuPai;

struct stLastHuInfo
{
	uint16_t seat;
	uint16_t times;
	stLastHuInfo()
	{
		seat = times = 0;
	}
};
typedef std::vector<stLastHuInfo> vecLastHuInfo;

// ��ׯ����
struct stLastBanker
{
	uint16_t seat;
	uint16_t times;
	stLastBanker()
	{
		seat = times = 0;
	}
};

// ÿ�κ�����ϸ
struct stHuDetail
{
	int16_t mySeat;		// �ҵ�λ��,����ҵ�λ�������λ����ͬ������ʾ�������粻ͬ��������
	int16_t huSeat;		// ����λ��
	int16_t doedSeat;	// ������λ��(-1:����,0����,1�¼�,2�Լ�,3�ϼ�)
	int16_t score;		// �Ӽ���
	int16_t huway;		// ���ķ�ʽ
	int16_t hutype;     // ��������
	int16_t humulti;    // ���ı���
	uint16_t huTile;	// ������

	int16_t item1;
	int16_t item2; 
	int16_t item3; 
	int16_t item4; 
	int16_t item5; 
	int16_t item6;
	int16_t item7;
	int16_t item8;
	int16_t item9;
	int16_t item10;
	int16_t item11;

	std::vector<int16_t> doedMultiSeat;

	stHuDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = huway = hutype = humulti = huTile = 0;
		item1 = item2 = item3 = item4 = item5 = item6 = item7 = item8 = item9 = item10 = item11 = 0;
	}

	void SetData(int16_t _mySeat, int16_t _huSeat,int16_t _doedSeat, int16_t _score, const stHuPai& huPai)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
		huway = huPai.m_eHupaiWay;
		hutype = huPai.m_eHupaiType;
		humulti = huPai.m_usMulti;
		huTile = huPai.m_usPai;
	}
};

// �η�����
struct stFengYuDetail
{
	int16_t mySeat;		// �ҵ�λ�� 
	int16_t huSeat;		// �ܵ�λ��
	int16_t doedSeat;	// ������λ��(-1:����,0����,1�¼�,2�Լ�,3�ϼ�)
	int16_t score;		// �Ӽ���
	int16_t fengYuType; // 1:�η���,2:����,3:����
	std::vector<uint16_t> doedMultiSeat; // �����������ID(����)
	stFengYuDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = fengYuType = 0;
	}
	void SetData(int16_t _mySeat, int16_t _huSeat, int16_t _doedSeat, int16_t _score, int16_t _fengYuType)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
		fengYuType = _fengYuType;
	}
};

// �黨��
struct stHuaZhuDetail
{
	int16_t mySeat;		// �ҵ�λ�� 
	int16_t huSeat;		// �����λ��
	int16_t doedSeat;	// ������λ��
	int16_t score;		// �Ӽ���
	stHuaZhuDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = 0;
	}
	void SetData(int16_t _mySeat, int16_t _huSeat, int16_t _doedSeat, int16_t _score)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
	}
};

// ����
struct stDaJiaoDetail
{
	int16_t mySeat;		// �ҵ�λ�� 
	int16_t huSeat;		// ��е�λ��
	int16_t doedSeat;	// ������λ��(-1:����,0����,1�¼�,2�Լ�,3�ϼ�)
	int16_t score;		// �Ӽ���
	stDaJiaoDetail()
	{
		mySeat = huSeat = doedSeat = -1;
		score = 0;
	}
	void SetData(int16_t _mySeat, int16_t _huSeat, int16_t _doedSeat, int16_t _score)
	{
		mySeat = _mySeat;
		huSeat = _huSeat;
		doedSeat = _doedSeat;
		score = _score;
	}
};

struct stScoreDetail
{
	int16_t			type;	// 1��,2�η�����,3����,4���,5��˰,6����ת��
	stHuDetail		hu;
	stFengYuDetail	fengYu;
	stHuaZhuDetail	huaZhu;
	stDaJiaoDetail	daJiao;
	int16_t			backTax;// ��˰
	int16_t			huJzy;	// ����ת��
};

// ������λ��
inline int16_t getOffsetPos(int16_t myPos, int16_t otherPos)
{
	if (otherPos < 0)
	{
		return -1;
	}
	if (myPos - otherPos == 0) {
		return 0;
	}
	else if (myPos - otherPos == -1 || myPos - otherPos == 3) {
		return 1;
	}
	else if (myPos - otherPos == 2 || myPos - otherPos == -2) {
		return 2;
	}
	else 
	{
		return 3;
	}
};

// ���ʵ��λ��-1:����,0����,1�¼�,2�Լ�,3�ϼ�
inline int16_t getActualPos(int16_t myPos,int16_t offsetPos)
{
	if (offsetPos < 0)
		return -1;

	if (offsetPos == 0)
		return myPos;

	return (myPos + offsetPos) % 4;
}

struct stGameResultSeat;
struct stReplayAction;

//
//	��־λ���� 
//
#define INSERT_FLAG(value, query_flags)	{(value) |= (query_flags);}
#define REMOVE_FLAG(value, query_flags)	{(value) &= ~(query_flags);}
#define HAS_FLAG(value, query_flags)		( ((value) & (query_flags)) != 0 ? true : false )

// ������α��
enum
{
	E_Check_Flag_NONE = 0,
	E_Check_Flag_PPH = 1,
	E_Check_Flag_HYS = 2,
	E_Check_Flag_QYS = 4,
	E_Check_Flag_ZYJ = 8,
	E_Check_Flag_QYJ = 16,
	E_Check_Flag_18LH = 32,
	E_Check_Flag_QIDUI = 64,
	E_Cehck_Flag_QFeng = 128,
	E_Check_Flag_HH = 256,
	E_Check_Flag_HH2 = 512,
	E_Check_Flag_HH3 = 1024,
	E_Check_Flag_MQ = 2048,
	E_Check_Flag_JJ = 4096,
};

/*
 * �齫�������
 * 
 * ����ƽ���齫������Ϊ�����������й�����磬�������Ϊͨ������(��ƽ��)�������ر�������Լ��ĺ�������
 *
 */
class CMajingRule
{
public:
	CRoom*		m_pRoom;
	CMaJiang*	m_pMaj;
	const ::msg_maj::RoomOption& m_roomOption;

	uint16_t m_usPayType;		// ֧������
	uint16_t m_usBaseScoreType;	// �׷�����
	uint16_t m_usMaiMaType;		// ��������
	bool m_bYiMaAllHit;			// һ��ȫ��
	uint16_t m_usJuShuType;		// ��������

	uint16_t m_usRenShuType;	// ��������1:2��,2:3��,
	uint16_t m_usFengDingType;	// �ⶥ

	uint32_t m_usWanFaVal;		// �����ำֵ

	bool m_bGhost;						//���й�
	bool m_bWuZi;						//������
	bool m_bCanPaoHu;					//���ں�
	bool m_bDaHuJiaBei;					//�ɴ��
	bool m_bGangShangPaoBao3Jia;		//�������Ƿ������
	bool m_bQiangGangBao3Jia;			//���ܺ��Ƿ������
	bool m_bGangKaiHuaIsBao3Jia;		//���ϻ��Ƿ������

	bool m_bJieHu;		// �Ƿ�غ�
	bool m_bGengZhuang; //�Ƿ��ׯ
	bool m_bIsGuoPeng;
	bool m_bIsGuoHu;
	bool m_bIsGuoGang;

	std::set<uint16_t>	m_setGhostPai; // ����

public:
	CMajingRule(CRoom* pRoom,const ::msg_maj::RoomOption& roomOption);
	virtual ~CMajingRule();
	inline void SetMajiang(CMaJiang* pMaj) { m_pMaj = pMaj; }
	inline void AddGhostPai(uint16_t usPai) { m_setGhostPai.insert(usPai); }

	// ���֧������
	inline uint16_t GetPayType() const { return m_usPayType; }
	inline uint16_t GetPlayerNum() const { return m_usRenShuType == 1 ? 4 : m_usRenShuType == 2 ? 3 : 2; }

	// �������ɺ�Ҫȥ����ѯ�ʵ��¼����������ӣ�û���¼���ֱ�ӷ�����
	virtual eRoomStatus AcceptAskAllNextStatus() const = 0;

	// ��������ȥ���Ľ�������״̬�ı�
	virtual eRoomStatus SendHandCardsAllNextState() const = 0;

	// ������ϣ�ǰ�˶�׼���õ��¼���������¼�����ȥ��������true������false��ֱ�ӷ���
	virtual eRoomStatus DisoverCardAllCheckAndDoEvent() const = 0;

	// �¾�׼����Ҫȥ�����¼�
	virtual bool PrepareRoundAllCheckAndDoAskSame() { return false; };

	// �������Notify
	virtual void ReconnectReadyReqCheckAndNotify(CPlayer* pPlayer) {};
	
	virtual bool IsGhost() const { return m_bGhost; }

	virtual bool IsWuZi() const { return m_bWuZi; }

	inline bool HasMaiMa() const { return m_usMaiMaType > 0; }

	inline bool IsYiMaAllHit() const { return m_bYiMaAllHit; }

	inline int32_t GetMaiMaNum() const { return m_usMaiMaType > 0 ?( (m_usMaiMaType - 1) * 2):0; }

	inline bool IsDaHuJiaBei() const { return m_bDaHuJiaBei; }

	inline int32_t GetTopScore() const {
		return  m_usFengDingType == 1 ? 20 : m_usFengDingType == 2 ? 50 : m_usFengDingType == 1 ? 100 : 99999;
	}

	// ���������
	virtual uint16_t GetTotalPaiNum() const;

	// ��ù����б�
	inline const std::set<uint16_t>& GetGhostList() const { return m_setGhostPai; };

	// �Ƿ�Ϊ���ƣ����ֹ�����Ҫ�õ���
	virtual bool IsGhostCard(uint16_t usPai);

	// ����ׯ����λ
	virtual uint16_t GetBankerSeat() = 0;

	// �ܵ��¼�
	void CountEventGang(uint16_t usSeat, uint16_t usEventType);

	virtual void CountEventMingGang(uint16_t usSeat);

	virtual void CountEventAnGang(uint16_t usSeat);

	virtual void CountEventGouShouGang(uint16_t usSeat);

	// �Ƿ���Բ���
	virtual bool CanBuGang(CPlayer* pPlayer, std::vector<uint16_t>& agpailist) { return true; }

	// �Ƿ���Է���(�����)
	virtual bool CanDianPao(CPlayer* pPlayer) { return m_bCanPaoHu; }

	// �Ƿ���Գ���
	virtual bool CanEatPai(CPlayer* pPlayer) { return false; }

	// �Ƿ���Ҫ
	virtual bool CanGang(CPlayer* pPlayer) { return true; }

	// �Ƿ���Ҫ�������
	virtual bool NeedGangZi(CPlayer* pPlayer) { return false; }

	// �Ƿ���Ҫ����
	virtual bool CanBaoTing() { return false; }

	// �Ƿ�������
	virtual bool CanTianHu() { return false; }

	// �Ƿ���Եغ�
	virtual bool CanDiHu() { return false; }

	// �Ƿ���Ժ�������
	virtual bool CanHaiDiLaoYue() { return false; }

	// ����������
	virtual void CheckHitMa(uint16_t usSeat, std::vector<uint16_t>& hitmalist) const;

	// ���㷬��
	virtual void CountResult() = 0;

	// ����ܷ�
	virtual void CountGangResult() = 0;

	virtual void CountGengZhuang(uint16_t usPai);

	// ����ʱ�����ٴﵽ�÷�������ȥ��
	virtual bool CanQiHuType(::msg_maj::hu_type huType) { return true;}

	virtual uint16_t GetGhostCard() { return 5; };

	// �������ٵķ�
	virtual uint16_t QiHuFanScore() { return 0; }

	// ��õ׷�
	virtual uint16_t GetBaseScore() const { return m_usBaseScoreType == 1?1: m_usBaseScoreType == 2?2: m_usBaseScoreType == 3?5:1;}

	// �Ƿ���ܷ� 
	virtual bool IsCanCountGang() { return true; }

	// �����ܲ��ܸ�
	virtual bool GhostCanGang() { return false; }

	// ��þ�����Ʒ�ʽ
	virtual ::msg_maj::hu_way GetHuWayZiMo() const { return ::msg_maj::hu_way_zimo; };
	virtual ::msg_maj::hu_way GetHuWayGangShanPao() const { return ::msg_maj::hu_way_gangshangpao; };
	virtual ::msg_maj::hu_way GetHuWayQiangGangHu() const { return ::msg_maj::hu_way_qiangganghu; };
	virtual ::msg_maj::hu_way GetHuWayGangKaiHua() const { return ::msg_maj::hu_way_gangkaihua; };
	virtual ::msg_maj::hu_way GetHuWayDiaoPao() const { return ::msg_maj::hu_way_none; };

	virtual ::msg_maj::hu_way GetHuWayTianHu() const { return ::msg_maj::hu_way_none; };
	virtual ::msg_maj::hu_way GetHuWayDiHu() const { return ::msg_maj::hu_way_none; };
	virtual ::msg_maj::hu_way GetHuWayHaiDiLaoYue() const { return ::msg_maj::hu_way_none; };

	virtual bool IsTianHu(CPlayer* pPlayer);
	virtual bool IsDiHu(CPlayer* pPlayer);

	// ��ܵķ���
	virtual uint16_t GetFanAnGang(CPlayer* pPlayer) const;
	virtual uint16_t GetFanMingGang(CPlayer* pPlayer) const;
	virtual uint16_t GetFanNextGang(CPlayer* pPlayer) const;

	// �Ƿ���Ը�����
	virtual bool GangShangPaoBao3Jia() const { return m_bGangShangPaoBao3Jia; }
	virtual bool QiangGangHuBao3Jia() const { return m_bQiangGangBao3Jia; }

	// �Ƿ����ܺ�������
	bool IsQiangGangHuBao3Jia(const stHuPai& sthupai) const;
	// �Ƿ�ܿ���������
	bool IsGangKaiHuaBao3Jia(const stHuPai& sthupai) const;

	// ������ĵķ���
	virtual uint16_t GetCostCard();

	virtual bool IsJieHu() const { return m_bJieHu; }

	virtual void SetHuInfo(const stHuPai& sthupai, uint16_t seat, ::msg_maj::HuInfo* huInfo,bool isFull = false) = 0;
	virtual void SetResultSeatHuInfo(const stGameResultSeat& seatData, ::msg_maj::HuInfo* huInfo) = 0;
	virtual void SetReplayActionHuInfo(const stReplayAction& actionData, ::msg_maj::HuInfo* huInfo) = 0;

	/*
	* ������ƵĻ�����
	*/
	virtual int32_t CountHupaiBaseScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, stHuDetail& huDetail) = 0;

	/*
	* ��������˵ķ�
	*/
	virtual void CountHupaiScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, std::pair<uint16_t, uint16_t>& out_mainfo) = 0;

	// �Ƿ����ڹ��˵��¼�����
	virtual bool IsMultiHues() const { return false; }
	virtual bool IsFliterPaiEvent(CPlayer* pPlayer, uint16_t usPai) const;
	virtual bool HuedCanSendCard(CPlayer* pPlayer) const;
	virtual bool HuedCanDiscard(CPlayer* pPlayer)const;
	virtual bool HuedCanEvent(CPlayer* pPlayer) const;
	virtual bool HuedCanGang(CPlayer* pPlayer) const;
	virtual bool HuedCanPeng(CPlayer* pPlayer) const;
	virtual bool HuedCanDiaoPao(CPlayer* pPlayer) const;
	virtual bool HuedCanGangShanPao(CPlayer* pPlayer) const;
	virtual bool HuedCanEnd() const { return true; }
	virtual bool HuedCanGangThisPai(const std::vector<uint16_t>& copy_pai_list, uint16_t usPai) { return false; }

	// ����������ʤ��
	virtual bool IsThisInnMyWin(CPlayer* pPlayer) const = 0;

public:

	//����Ƿ���ƣ��ţ�  
	bool    CheckAAPai(int iValue1, int iValue2);
	//����Ƿ�������  
	bool    CheckABCPai(int iValue1, int iValue2, int iValu3);
	//����Ƿ�������  
	bool    CheckABCDPai(int iValue1, int iValue2, int iValu3, int iValue4);
	//����Ƿ�������  
	bool    CheckABCDEFGPai(int iValue1, int iValue2, int iValu3, int iValue4, int iValue5, int iValue6, int iValue7);
	//����Ƿ�������  
	bool    CheckAAAPai(int iValue1, int iValue2, int iValu3);
	//����Ƿ�������  
	bool    CheckAAAAPai(int iValue1, int iValue2, int iValu3, int iValue4);
	//����Ƿ�������  
	bool    CheckAABBCCPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6);

	// ɾ��AA ��ָ��
	bool DelAAPai_NULL(vecCheckPai& stlist);
	// ɾ��AA ָ����
	bool DelAAPai_Pai(vecCheckPai& stlist, uint16_t usPai);
	// ɾ��AA ��������
	bool DelAAPai_Num(vecCheckPai& stlist, uint16_t& usNum);
	// ɾ��AAA
	bool DelAAAPai(vecCheckPai& stlist);
	// ɾ��AAA ABC
	bool DelAAAABCPai(vecCheckPai& stlist);
	// ɾ��AAA ABC ��
	bool DelAAAABCPai_ting(vecCheckPai& stlist);
	// ɾ��AAA ABC ����
	bool DelAAAABCPaiEx(vecCheckPai& stlist);
	// ɾ��AAA ABC ���� ��
	bool DelAAAABCPaiEx_ting(vecCheckPai& stlist);
	// ɾ��AAA ABC ����˳��
	bool DelAAAABCJC_ting(vecCheckPai& stlist);
	// ɾ��AAA ABC ɾ��ͷ˳��
	bool DelAAAABCHead_ting(vecCheckPai& stlist);
	// ɾ��AAA ABC ��������
	bool DelAAAABCJCEx_ting(vecCheckPai& stlist);
	// ɾ��AAA ABC ɾ��ͷ����
	bool DelAAAABCHeadEx_ting(vecCheckPai& stlist);
	// ɾ��ABC ˳��
	bool DelABCPai(vecCheckPai& stlist);
	// ɾ��ABC ����
	bool DelABCPaiEx(vecCheckPai& stlist);
	// ɾ��AA AB AC ˳��
	bool DelAAABACPai(vecCheckPai& stlist, uint16_t& usNum);
	// ɾ��AA AB AC ����
	bool DelAAABACPaiEx(vecCheckPai& stlist, uint16_t& usNum);
	// ɾ��AABBCC
	bool DelAABBCC(vecCheckPai& stlist, uint16_t& usNum);
	// ɾ��ABC ��ͷɾ��
	bool DelAAAABC_Head(vecCheckPai& stlist);
	// ɾ��AC ��ͷɾ��
	bool DelAAAC_Head(vecCheckPai& stlist);

public: //�ṹ���ƹ���

	// ɾ���Ѿ������ƣ�ĳ��λ�ã���ͬ����
	void DelHasCheckPai(std::vector<uint16_t>& pailist, uint16_t usStartIndex, uint16_t usNum);
	// ɾ������Ľṹ���ƣ�ĳ��λ�ã���ͬ��ʽ  usNum    1��ABC	2��ABAC    3��AAA	4��AA
	void DelStructPai(vecCheckPai& pailist, uint16_t usPos, uint16_t usNum);
	// �����ƽṹ
	bool CheckStructPai(vecCheckPai& pailist);
	//����Ƿ��нṹ����(β������)
	bool CheckStructPai1Or9(vecCheckPai& pailist);
	//����Ƿ��нṹ����
	bool CheckHasStructPai(const vecCheckPai& pailist, uint16_t usPai);
	// �ı�ṹ
	void ChangeStructPai(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist);
	// �ı�ṹ
	void ChangeStructPai_Ghost(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist, uint16_t& usGhostNum);
	// �ı�ṹ-�Զ����
	void ChangeStructPai_Ghost_Custom(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist, uint16_t& usGhostNum,uint16_t usCusGhostPai);
	// �ı�ṹ
	void ChangeStructPai_Ex(const std::vector<uint16_t>& pailist, uint16_t& usGhostNum, vecCheckPai& zilist, vecCheckPai& tonglist, vecCheckPai& tiaolist, vecCheckPai& wanlist);
	// ��ȡ��ͬ�����ĸ���
	void GetSamePaiNumNum(const vecCheckPai& pailist, uint16_t& usNum1, uint16_t& usNum2, uint16_t& usNum3, uint16_t& usNum4);

public: //�¼���

	// ��ⰵ��
	void CheckAnGang(const std::vector<uint16_t>& pailist, std::vector<uint16_t>& agpailist);
	// ������  
	bool CheckGangPai(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// �������  
	bool CheckPengPai(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// ������
	bool CheckEatPai(const std::vector<uint16_t>& pailist, uint16_t usPai,std::set<uint16_t>& out_eatlist);

	//������(�ܵ��ýӿ�)
	virtual ::msg_maj::hu_type CheckHupaiAll(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist,uint16_t usTingPai = 0) = 0;

protected: //��ͨ����

	//-------------------------------------ƽ��-��Χ--------------------------------------------------
	// ���ƽ��
	bool CheckHupai_PingHu(const std::vector<uint16_t>& pailist);
	// ��19˳��19��
	bool CheckHupai_PingHu_AbcJJ19(const std::vector<uint16_t>& pailist);
	// ���ƽ��
	bool CheckHupai_PingHu_Jiang258(const std::vector<uint16_t>& pailist);
	// ������
	bool IsPPHu(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);	// AAAX,BBBX,CCCX,DDD,EE
	
	// �Ƿ�����
	bool IsMq(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// �Ƿ񽫽�(��ƽ����������ж�)
	bool IsJJHu(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// ��һɫ
	bool IsHys(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// ��һɫ
	bool IsQys(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// ���۾�
	bool IsDuanYj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// ���۾�
	bool IsDaiYj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// �����(����ȫ����)
	bool IsJingGG(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// ���۾�
	bool IsZyj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	// ȫ�۾�
	bool IsQyj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//18�޺�
	bool Is18Lh(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//����(ֻ���7��Ч,��Ҫȷ��7�Ժ���ж��Ƿ�Ϊ����)
	uint16_t CheckHhNum(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);
	bool IsHh(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);
	bool IsHh2(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);
	bool IsHh3(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//ȫ����
	bool IsQuanQiuRen(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//-------------------------------------�߶�-��Χ---------------------------------------------------
	// ����߶�
	bool CheckHupai_QiDui(const std::vector<uint16_t>& pailist);

	//-------------------------------------ȫ��ͷ-��Χ---------------------------------------------------
	bool CheckHupai_QuangFeng(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost);

	//-------------------------------------13Ҫ-��Χ---------------------------------------------------
	// ���ʮ����
	bool CheckHupai_13yao(const std::vector<uint16_t>& pailist);

public:
	// �Ƿ�Ϊ��Ͳ��258����
	bool Is258(uint16_t usPai);
	// �Ƿ�Ϊ1��1��
	bool Is1Or9(uint16_t usPai);
public: //��Ӻ���

	// ���Ͳ����������Ҫ�Ĺ����������޽�
	uint16_t CheckNeedGhostNum(const vecCheckPai& stlist_yuan);

	// ���Ͳ����������Ҫ�Ĺ����������н�
	uint16_t CheckNeedGhostNum_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang);
	// ���Ͳ����������Ҫ�Ĺ����������н�
	uint16_t CheckNeedGhostNum_Jiang_258(const vecCheckPai& stlist_yuan, bool& bJiang);
	// ���Ͳ����������Ҫ�Ĺ����������н���������Ϊ��
	uint16_t CheckNeedGhostNum1_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang);
	// ���Ͳ����������Ҫ�Ĺ����������н���������Ϊ��������
	uint16_t CheckNeedGhostNum1_JiangEx(const vecCheckPai& stlist_yuan, bool& bJiang);
	// ���Ͳ����������Ҫ�Ĺ����������н�������Ϊ��
	uint16_t CheckNeedGhostNum2_Jiang(const vecCheckPai& stlist_yuan);

	// �������Ҫ�Ĺ����������޽�
	uint16_t CheckNeedGhostNumZi(const vecCheckPai& zilist_yuan);

	// ���������Ҫ�Ĺ����������н�
	uint16_t CheckNeedGhostNumZi_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang);

	// ���ƽ��_����
	bool CheckHupai_PingHu_Ghost(const std::vector<uint16_t>& pailist);

	// ���ƽ��_����
	bool CheckHupai_PingHu_Ghost_Jiang258(const std::vector<uint16_t>& pailist);

	// ��ȡƽ������ 0����ͨƽ�� 1������ 2�������
	uint16_t GetQiDuiType(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// ��ȡƽ������ 0����ͨƽ�� 1������ 2�������
	uint16_t GetPingHuType(const std::vector<uint16_t>& pailist, uint16_t usPai);
	// ������߶�_����
	bool CheckHupai_QiDui_Ghost(const std::vector<uint16_t>& pailist);
	// ���ʮ����_����
	bool CheckHupai_13yao_Ghost(const std::vector<uint16_t>& pailist);

public: // ����
	// �����
	void Display(const std::vector<uint16_t>& pailist);
	void DisplayEx(const std::vector<uint16_t>& pailist, uint16_t usNum);
	// ������
	void AddPai(std::vector<uint16_t> & pailist, uint16_t usPai);
	// ��ȡ���ƣ����ڣ�����
	void GetGuJianXiang(const std::vector<uint16_t>& pailist, std::vector<uint16_t>& gulist, std::vector<uint16_t>& jianlist, std::vector<uint16_t>& xianglist, std::vector<uint16_t>& samelist);
	// ��֤��
	bool VerifyPai(uint16_t usGhostNum, const std::vector<uint16_t> & pailist);

public: //����
	// ��������
	void AddTingPai(std::set<uint16_t>& tinglist, uint16_t usPai);
	// ��������
	void AddTingPaiEx(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// ��ȡ���Ƶ��ƣ��޽�
	void GetTingPaiList(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// ��ȡ���Ƶ��ƣ��н�
	void GetTingPaiList_Jiang(const vecCheckPai& stlist, uint16_t usJiangPai, std::set<uint16_t>& tinglist);
	// ��ȡ�����б��֣��޽�
	void GetTingPaiListZi(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// ��ȡ�����б��֣��н�
	void GetTingPaiListZi_Jiang(const vecCheckPai& stlist, std::set<uint16_t>& tinglist);
	// ������ƣ�ƽ��
	bool CheckTing_PingHu(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// ������߶�
	bool CheckTing_QiDui(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// �����ʮ����
	bool CheckTing_13yao(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// �������(0������,1�����߶�,2����ƽ��)
	virtual int16_t CheckTingPai(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist);
	// �黨��
	virtual void ChaHuaZhu() {};
	// ����
	virtual void ChaDaJiao() {};

	// �Ƿ��й���
	virtual bool IsGuoHu() { return m_bIsGuoHu; }

	// �Ƿ��й���
	virtual bool IsGuoPeng() { return m_bIsGuoPeng; }

	// �Ƿ��й���
	virtual bool IsGuoGang() { return m_bIsGuoGang; }

	// �Ƿ��й���������
	virtual bool IsGuoPengThisPai(CPlayer* pPlayer, uint16_t usPai) { return false; }

	// �Ƿ��й���
	virtual bool IsHasGhostPai(const std::vector<uint16_t>& pailist);

};

#endif