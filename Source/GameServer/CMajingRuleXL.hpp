#ifndef __MAJIANG_RULE_XL_TDH_H__
#define __MAJIANG_RULE_XL_TDH_H__

#include "Global.hpp"
#include "CMajingRule.hpp"

/*
* ��Դ�Ƶ����齫
*/
class CMajingRuleXL : public CMajingRule
{
public:
	CMajingRuleXL(CRoom* pRoom, const ::msg_maj::RoomOption& roomOption);
	virtual ~CMajingRuleXL();

	virtual void SetRoomRoomOption(const ::msg_maj::RoomOption& m_roomOption);

	virtual bool IsGhost() const { return m_bGhost; }

	virtual bool IsWuZi() const { return m_bWuZi; }

	virtual uint16_t GetTotalPaiNum(CRoom* pRoom);

	// ��ù���
	virtual uint16_t GetGhostCard() { return 5; };

	virtual bool IsGhostCard(CRoom* pRoom, uint16_t usPai);

	// ����ׯ����λ
	virtual uint16_t GetBankerSeat();

	// ���ƽ��
	virtual bool CheckHupai_PingHu(const std::vector<uint16_t>& pailist);

	virtual void CountEventMingGang(uint16_t usSeat);

	virtual void CountEventAnGang(uint16_t usSeat);

	virtual void CountEventGouShouGang(uint16_t usSeat);

	virtual bool CanDianPao(CPlayer* pPlayer);


	// ���㷬��
	virtual void CountResult();

	virtual void CountGangResult() {}

	// ������(��)
	virtual ::msg_maj::hu_type CheckHupaiAll(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist,uint16_t usTingPai = 0);

	// �����ƹ���
	virtual ::msg_maj::hu_type CheckHupaiAndGhost(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, uint16_t usTingPai = 0);

	// ��ÿ��������
	virtual uint16_t GetMaPaiNum(uint16_t nMaType);

	virtual eRoomStatus AcceptAskAllNextStatus() const;

	virtual ::msg_maj::hu_way GetHuWayZiMo() const;
	virtual ::msg_maj::hu_way GetHuWayGangShanPao() const { return ::msg_maj::hu_way_xl_gangshangpao; };
	virtual ::msg_maj::hu_way GetHuWayQiangGangHu() const { return ::msg_maj::hu_way_xl_qiangganghu; };
	virtual ::msg_maj::hu_way GetHuWayGangKaiHua() const { return ::msg_maj::hu_way_xl_gangkaihua; };
	virtual ::msg_maj::hu_way GetHuWayDiaoPao() const;

	virtual bool CanBuGang(CPlayer* pPlayer, std::vector<uint16_t>& agpailist);

	virtual bool CanGangShangPao(CPlayer* usPlayer) const { return true; }

	virtual bool GhostCanGang(CRoom* pRoom) { return true; }

	/*
	* �������Ӳ��������Ϣ
	*/
	void GetHitMaDatas(const stHuPai& sthupai, uint16_t& hitMaTimes);

	/*
	* ������ƵĻ�����
	*/
	virtual int32_t CountHupaiBaseScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, stHuDetail& huDetail);

	/*
	* ��������˵ķ�
	*/
	virtual void CountHupaiScore(const stHuPai& sthupai, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, std::pair<uint16_t, uint16_t>& out_mainfo);

	virtual bool IsJieHu() const { return false; }

	virtual void SetHuInfo(const stHuPai& sthupai, uint16_t seat, ::msg_maj::HuInfo* huInfo, bool isFull);
	virtual void SetResultSeatHuInfo(const stGameResultSeat& seatData, ::msg_maj::HuInfo* huInfo);
	virtual void SetReplayActionHuInfo(const stReplayAction& actionData, ::msg_maj::HuInfo* huInfo);

	virtual eRoomStatus SendHandCardsAllNextState() const;

	virtual eRoomStatus DisoverCardAllCheckAndDoEvent() const;

	// �黨��
	virtual void ChaHuaZhu(CRoom* pRoom);
	// ����
	virtual void ChaDaJiao(CRoom* pRoom);

	// �Ƿ����ڹ��˵��¼�����
	virtual bool IsMultiHues() const { return true; }
	virtual bool IsFliterPaiEvent(CPlayer* pPlayer, uint16_t usPai) const;
	virtual bool HuedCanSendCard(CPlayer* pPlayer) const;
	virtual bool HuedCanDiscard(CPlayer* pPlayer)const;
	virtual bool HuedCanEvent(CPlayer* pPlayer) const;
	virtual bool HuedCanGang(CPlayer* pPlayer) const;
	virtual bool HuedCanPeng(CPlayer* pPlayer) const;
	virtual bool HuedCanDiaoPao(CPlayer* pPlayer) const;
	virtual bool HuedCanGangShanPao(CPlayer* pPlayer) const;
	virtual bool HuedCanEnd(CRoom* pRoom) const;
	virtual bool HuedCanGangThisPai(CRoom* pRoom, const std::vector<uint16_t>& copy_pai_list, uint16_t usPai);

	virtual bool IsThisInnMyWin(CPlayer* pPlayer) const;

	inline bool IsSanZhang() const { return m_bSanZhang; }
	inline bool IsDingQue() const { return m_bDingQue; }
	inline bool IsHuJiaoZhuanYu() const { return m_bHuJiaoZhuanYu; }
	inline bool IsDaiYj() const { return m_bIsDaiYj; }
	inline bool IsDuanYj() const { return m_bIsDuanYj; }
	inline bool IsJiangjgg() const { return m_bIsJiangJGG; }
	inline bool IsMengQing() const { return m_bIsMenQing; }
	inline bool IsTianDihu() const { return m_bTianDihu; }

private:

	bool m_bSanZhang;						//������
	bool m_bDingQue;						//��ȱ��
	bool m_bHuJiaoZhuanYu;					//����ת��
	int16_t m_usSanZhangStep;				//���Ƶ�ǰ�Ĳ���

	bool m_bIsDaiYj;
	bool m_bIsDuanYj;
	bool m_bIsJiangJGG;
	bool m_bIsMenQing;
	bool m_bTianDihu;
	bool m_bHaiDiLaoYue;

};

#endif