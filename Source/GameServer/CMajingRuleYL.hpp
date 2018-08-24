#ifndef __MAJIANG_RULE_yl_TDH_H__
#define __MAJIANG_RULE_yl_TDH_H__

#include "Global.hpp"
#include "CMajingRule.hpp"

/*
 * ��Դ�Ƶ����齫
 */
class CMajingRuleYL : public CMajingRule
{
public:
	CMajingRuleYL(CRoom* pRoom,const ::msg_maj::RoomOption& roomOption);
	virtual ~CMajingRuleYL();

	// ��ù���
	virtual uint16_t GetGhostCard() { return 5; };

	// ����ׯ����λ
	virtual uint16_t GetBankerSeat();

	// ���ƽ��
	virtual bool CheckHupai_PingHu(const std::vector<uint16_t>& pailist);

	virtual void CountEventMingGang(uint16_t usSeat);

	virtual void CountEventAnGang(uint16_t usSeat);

	virtual void CountEventGouShouGang(uint16_t usSeat);

	virtual bool CanDianPao(CPlayer* pPlayer);

	// �Ƿ���ܷ� 
	virtual bool IsCanCountGang();

	// ���㷬��
	virtual void CountResult();

	virtual void CountGangResult();

	// ������(��)
	virtual ::msg_maj::hu_type CheckHupaiAll(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, uint16_t usTingPai = 0);

	// �����ƹ���
	virtual ::msg_maj::hu_type CheckHupaiAndGhost(CPlayer* pPlayer, const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, uint16_t usTingPai = 0);

	virtual ::msg_maj::hu_way GetHuWayZiMo() const { return ::msg_maj::hu_way_yl_zimo; };
	virtual ::msg_maj::hu_way GetHuWayGangShanPao() const { return ::msg_maj::hu_way_yl_gangshangpao; };
	virtual ::msg_maj::hu_way GetHuWayQiangGangHu() const { return ::msg_maj::hu_way_yl_qiangganghu; };
	virtual ::msg_maj::hu_way GetHuWayGangKaiHua() const { return ::msg_maj::hu_way_yl_gangkaihua; };
	virtual ::msg_maj::hu_way GetHuWayDiaoPao() const { return ::msg_maj::hu_way_yl_dianpao; };

	virtual bool CanBuGang(CPlayer* pPlayer, std::vector<uint16_t>& agpailist);

	virtual bool GangShangPaoBao3Jia() const { return false; }

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

	 /*
	 * ��������˵ķ�(���˺�����)
	 */
	void CountGangScore(const stHuPai& sthupai, uint16_t gangSeat);

	virtual void SetHuInfo(const stHuPai& sthupai, uint16_t seat,::msg_maj::HuInfo* huInfo, bool isFull);
	virtual void SetResultSeatHuInfo(const stGameResultSeat& seatData, ::msg_maj::HuInfo* huInfo);
	virtual void SetReplayActionHuInfo(const stReplayAction& actionData, ::msg_maj::HuInfo* huInfo);
	
	virtual bool IsThisInnMyWin(CPlayer* pPlayer) const;

	virtual bool IsGuoPengThisPai(CPlayer* pPlayer, uint16_t usPai);

	virtual eRoomStatus AcceptAskAllNextStatus() const;

	virtual eRoomStatus SendHandCardsAllNextState() const;

	virtual eRoomStatus DisoverCardAllCheckAndDoEvent() const;
};

#endif