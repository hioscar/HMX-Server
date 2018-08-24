#ifndef _CROBOT_HPP_
#define _CROBOT_HPP_

#include "SrvEngine.h"
#include "FogsTimerService.hpp"

enum eActionType
{
	eActionType_NULL			= 0, //��
	eActionType_Login			= 1, //��¼
	eActionType_OpenRoom		= 2, //����
	eActionType_EnterReady		= 3, //���뷿����سɹ�
	eActionType_StartGame		= 4, //��ʼ��Ϸ
	eActionType_AcceptStart		= 5, //���ܿ�ʼ
	eActionType_AgreeDismiss	= 6, //ͬ���ɢ
	eActionType_ZiMo			= 7, //�����¼�
	eActionType_DianPao			= 8, //�����¼�
	eActionType_MingGang		= 9, //����
	eActionType_AnGang			= 10, //����
	eActionType_GuoShouGang		= 11, //���ָ�
	eActionType_Peng			= 12, //��
	eActionType_Pass			= 13, //��(�к���ʱѡ���)
	eActionType_RoundPrepare	= 14, //׼����һ��
	eActionType_Discard			= 15, //����
	eActionType_HuanSanZhang	= 16, //������
	eActionType_DingQue			= 17, //��ȱ
	eActionType_Num
};

/*
 *  ����AI����
 */
class CRobot : public zEntry
{
public:
	CRobot(zSession* pSession,const std::string& strAccount, uint32_t unSessionID,uint64_t uid);
	~CRobot();

	virtual inline uint64_t GetID(){ return _entry_id; }
	virtual inline uint64_t GetTempID(){ return _entry_tempid; }
	virtual inline const std::string& GetName(){ return _entry_name; }

	bool Init();
	void NextReset(); // �¾�����
	void Release();

	void SetActionType(eActionType etype);
	
	void Timer();	// ��ʱ��������ɷ�����ð�����

	void StopDismissRoom();

	// �����ķ������

	void SendLoginReq();		// ��¼
	void SendCreateRoomReq();	// ��������
	void SendJoinRoomReq(uint32_t roomID);		// ���뷿��
	void SendJoinReadyReq();
	void SendStartGame();		// ��ʼ׼��(ׯ��)
	void SendAcceptStart();		// ���Ϳ�ʼ(�м�)
	void SendDisoverCard();		// ������Ͼ�

	void SendRoundPrepare();
	void SendLeaveRoom();
	void SendDismissRoomReq();
	void SendAgreeDismiss();
	void SendReconnectOtherReady();


	inline uint32_t GetID32() const { return m_unSessionID; }
	inline uint64_t GetID64() const { return m_unSessionID; }
	inline const std::string& GetAccount() const{ return m_strAccount; }

	bool IsGhostPai(uint16_t usPai);

	void Display();
	void DiscardReq(uint16_t usPai);
	void HuanSanZhangReq();
	void DingQueReq();
	void RespZiMoPai(uint16_t usPai);
	void RespPassPai(uint16_t usPai);
	void RespDiaoPaoHu(uint16_t usPai);
	void RespMingGang(uint16_t usPai);
	void RespAnGang(uint16_t usPai);
	void RespGuoShouGang(uint16_t usPai);
	void RespPong(uint16_t usPai);

	void FitlerFai(uint16_t usPai,int16_t num);

	inline void SeatMySeat(int16_t _seat) { m_usSeat = _seat; }

	//����Ƿ�������  
	inline bool CheckABCPai(int iValue1, int iValue2, int iValue3)
	{
		if (iValue1 == (iValue2 - 1) && iValue2 == (iValue3 - 1))return true;
		return false;
	}

	inline bool CheckABCDPai(int iValue1, int iValue2, int iValue3, int iValue4)
	{
		if (iValue1 == (iValue2 - 1) && iValue2 == (iValue3 - 1) && iValue3 == (iValue4 - 1))return true;
		return false;
	}

	inline bool CheckABCDEFGPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7)
	{
		if (iValue1 == (iValue2 - 1) &&
			iValue2 == (iValue3 - 1) &&
			iValue3 == (iValue4 - 1) &&
			iValue4 == (iValue5 - 1) &&
			iValue5 == (iValue6 - 1) &&
			iValue6 == (iValue7 - 1))
		{
			return true;
		}

		return false;
	}

public:

	fogs::FogsTimer*  m_pTimer;
	zSession* m_pSession;

	bool m_bGhost;
	bool m_bClickDismiss;
	eActionType m_eActionType;

	std::string m_strAccount;
	uint64_t& m_unSessionID;

	uint64_t m_usUid;
	uint32_t m_nRoomID;
	uint16_t m_uCurrInnID;
	uint16_t m_uTotalInnCount;
	int16_t m_usSeat;
	uint16_t m_usPai;
	uint16_t m_uQueType;

	bool bIsRoomer;
	bool bIsBanker; // �Ƿ�Ϊׯ��
	bool bIsLogin_1;
	bool bIsLogin_2;
	bool bIsSendCreate_1;
	bool bIsSendCreate_2;
	bool bIsSendJoin_1;
	bool bIsSendJoin_2;
	bool bIsSendJoinReady_1;
	bool bIsSendJoinReady_2;


	bool bIsStartGame_1;
	bool bIsStartGame_2;
	bool bIsSendAcceptStart_1;
	bool bIsSendAcceptStart_2;
	bool bIsDisoverCard;

	bool bIsPlaying;

	bool bIsCanHu;
	bool bIsCanGang;
	bool bIsCanPeng;
	bool bIsCanDiscard;

	bool bIsDismiss;
	bool bIsTingpai;

	::msg_maj::Role role;
	::msg_maj::StartRoundResp myPaiData;
	::msg_maj::DealNotify     dealNotify;
	::msg_maj::TingPaiDiscardNotify	tingPaiDiscardNotify;


};

#endif // !_CROBOT_HPP_
