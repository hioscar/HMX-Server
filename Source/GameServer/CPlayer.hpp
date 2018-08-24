#ifndef _CPLAYER_H_ 
#define _CPLAYER_H_
#include <boost/pool/object_pool.hpp>
#include "Global.hpp"
#include "google/protobuf/message.h"
#include "CMajingRule.hpp"
#include "FogsTimerService.hpp"

static const uint16_t g_usPaiNum = 14;
class CRoom;

// λ����Ϣ
struct stGpsInfo
{
	stGpsInfo()
	{
		reset();
	}
	stGpsInfo(const stGpsInfo& info)
	{
		operator=(info);
	}
	stGpsInfo& operator=(const stGpsInfo& info)
	{
		longitude = info.longitude;
		latitude = info.latitude;
		return *this;
	}
	void reset()
	{
		longitude = latitude = 999.0;
	}
	bool isOk() const
	{
		return longitude > 0 && longitude < 180 && latitude > 0 && latitude < 180;
	}
	double longitude; 	// ����
	double latitude;	// ΰ��
	std::string address; // ip��ʵ�ʵ�ַ
};

class CPlayer
{
public:

	CPlayer(uint64_t unSessionID, uint32_t unFepServerID, const ::msg_maj::Role& proData);
	virtual ~CPlayer();
	
	bool Init();

	void RefreshData(bool bBackground);

	bool InitPlayer();

	bool LeaveGame();

	bool EnterGame();

	bool Disconnect();

	void SetDisconnect(bool bDisconnect) 
	{ 
		m_bDisconnect = bDisconnect; 
		if (!bDisconnect)
		{
			m_tDisconnectTime = 0;
		}
	}

	bool IsDisconnect() { return m_bDisconnect; }

	time_t GetDisconnectTime() const { return m_tDisconnectTime; }

	void LeaveRoomEx();

	void Share();

	void SendLoginMsg(bool bDisconnect);

	void SendNotifyAnotherLogin();

	void SendSyncActivityInfo();

	void SendRoleData(CPlayer* lookPlayer = NULL);

	void SendRoomCards(CPlayer* lookPlayer = NULL);

	void CreateRoom();
	void JoinRoom(uint32_t room_id);
	
	/*
	 * type : 0��������,1���߱���
	 */
	void SaveDataToDB(int32_t type = 0);

	void SetRoleProto(::msg_maj::Role* pPro);

	void SetRoleInfoProto(msg_maj::RoleInfo* pPro);

	void SetSeatInfoProto(msg_maj::SeatInfo* pPro, bool bReconnect = false) const;

	void SetTotalResultProto(msg_maj::TotalResultSeat* pPro);

	void SendMsgToClient(uint16_t usCmd, uint16_t usCCmd, const google::protobuf::Message& proData);

	//
	template<typename T1, typename T2, typename T3>
	inline void SendErrorCode(::msg_event::tip_type tip_type, const T1& t1, const T2& t2, const T3& t3)
	{
		std::stringstream ss;
		ss << t1 << "," << t2 << "," << t3;
		::msg_event::TipResp proto;
		proto.set_type(tip_type);
		proto.set_args(ss.str());
		SendMsgToClient(::comdef::msg_event,::msg_event::tip_nt_resp,proto);
	}

	void UpdateTopToRank(::msg_maj::rank_type rank_t);
	void UpdateToGate();

	bool IsGhostHu(CMajingRule* pRule);

	uint16_t GetSanZhangLessType();
	uint16_t GetDingQueLessType();

public:

	bool CheckPaiNum();

	bool AddPai(uint16_t usPai);

	const std::vector<uint16_t>& GetPaiList() { return m_vecPai; }

	const std::vector<uint16_t>& GetDicardPaiList() { return m_vecDicardPai; }

	const vecEventPai& GetEventPaiList() { return m_vecEventPai; }

	inline std::vector<uint16_t>& GetHitMa() { return m_vecHitMa; }

	inline std::vector<uint16_t>& GetPengSeat() { return m_vecPengSeat; }

	inline void AddPengSeat(uint16_t usSeat) { m_vecPengSeat.push_back(usSeat); }

	bool DiscardTile(uint16_t usPai);

	void ResetRoomData();

	void ResetMajData();

	bool DelPai(uint16_t usPai);

	bool PengPai(uint16_t usPai);

	bool MingGang(uint16_t usPai);

	void MingGangSeated(uint16_t usSeat);

	inline const std::vector<uint16_t>& GetMingGangSeated() const { return m_vecFanMingGangSeated; }

	bool AnGang(uint16_t usPai);

	bool NextGang(uint16_t usPai, bool bEvent);

	void AddEventPai(uint16_t usType, uint16_t usPai);

	void DelEventPai(uint16_t usType, uint16_t usPai);

	void DelDiscardPai(uint16_t usPai);

public:

	inline uint64_t GetCharID() const { return m_ulCharID; }
	inline const std::string GetAccount() { return m_strAccount; }
	inline int32_t GetSessionID() const { return m_unSessionID; }
	inline void SetSessionID(uint32_t unSessionID) { m_unSessionID = unSessionID; }
	inline const std::string& GetCharName() const { return m_strCharName; }
	inline void SetCharName(const std::string& strName) { m_strCharName = strName; }
	inline int32_t GetLevel() const { return m_nLevel; }
	inline void SetLevel(int32_t nLevel) { m_nLevel = nLevel; SetDirtyData(); }
	inline const std::string& GetLogoIcon() const { return m_strLogoIcon; }
	inline void SetLogoIcon(const std::string& strIcon) { m_strLogoIcon = strIcon; }
	inline int32_t GetTitle() const { return m_nTitle; }
	inline void SetTitle(int32_t nTitle) { m_nTitle = nTitle; SetDirtyData(); }
	inline int32_t GetDiamond() const { return m_nDiamond; }
	inline void SetDiamond(int32_t nDiamond) { m_nDiamond = nDiamond; SetDirtyData(); }
	inline int32_t GetCoin() const { return m_nCoin; }
	inline void SetCoin(int32_t nCoin) { m_nCoin = nCoin; SetDirtyData(); }
	inline int32_t GetSexual() const { return m_usSexual; }
	inline void SetSexual(int32_t nSexual) { m_usSexual = nSexual; SetDirtyData(); }

	inline int32_t GetRoomCard() const { return m_nRoomCards; }
	inline void SetRoomCard(int32_t nCards) { m_nRoomCards = nCards; SetDirtyData(); }
	inline int32_t GetTotalGames() const { return m_nTotalGames; }
	inline void SetTotalGames(int32_t nGames) { m_nTotalGames = nGames; SetDirtyData(); }
	inline int32_t GetWinGames() const { return m_nWinGames; } // todo ��Ҫ�����ܼ�¼ 
	inline void SetWinGames(int32_t nGames) { m_nWinGames = nGames; SetDirtyData(); }
	inline int32_t GetConGames() const { return m_nConGames; }
	inline void SetConGames(int32_t nGames) {
		m_nConGames = nGames;
		if (m_nConGames > m_nHisConGames) m_nHisConGames = m_nConGames;
		SetDirtyData();
	}
	inline int32_t GetHisConGame() const { return m_nHisConGames; }
	inline int32_t GetHisMaxScore() const { return m_nHisMaxScore; }
	inline void SetHisMaxScore(int32_t nScore) { m_nHisMaxScore = nScore; SetDirtyData(); }
	inline int32_t GetWeekMaxScore() const { return m_nWeekMaxScore; }
	inline void SetWeekMaxScore(int32_t nScore) { m_nWeekMaxScore = nScore; SetDirtyData(); }
	void AddTodayPlayNum(int32_t num);

	inline uint32_t GetFirstShowStatus() const { return m_unFirstShowStatus; }
	inline void SetFirstShowStatus(uint32_t unStatus) { m_unFirstShowStatus = unStatus; SetDirtyData(); }
	inline uint32_t GetHasInvFriendNum() const { return m_unHasInvFriendNum; }
	inline uint32_t GetHasGetRoomCard() const { return m_unHasGetRoomCard; }
	inline void SetHasGetRoomCard(uint32_t unRoomCard) { m_unHasGetRoomCard = unRoomCard; SetDirtyData(); }
	inline uint32_t GetCanGetRoomCard() const { return m_unCanGetRoomCard; }
	inline void SetCanGetRoomCard(uint32_t unRoomCard) { m_unCanGetRoomCard = unRoomCard; SetDirtyData(); }

	inline uint32_t GetBeInvitationID() const { return m_unBeInvitationID; }
	inline void SetBeInvitationID(uint32_t unID) { m_unBeInvitationID = unID; }
	inline const std::string& GetBeInvitationName() { return m_strBeInvitationName; }
	inline void SetBeInvitationName(const std::string& strName) { m_strBeInvitationName = strName; }
	inline uint32_t GetPlayGames() const { return m_unPlayGames; }
	inline void SetPlayGames(uint32_t unGames) { m_unPlayGames = unGames; }
	inline uint32_t GetRecvRewardStatus() const { return m_unRecvRewardStatus; }
	inline void SetRecvRewardStatus(uint32_t unStatus) { m_unRecvRewardStatus = unStatus; }

	void SetDirtyData();

	inline uint32_t GetRoomID() const { return m_unRoomID; }
	inline void SetRoomID(uint32_t unRoomID) { m_unRoomID = unRoomID; }
	inline uint16_t GetSeat() const { return m_usSeat; }
	inline void SetSeat(uint16_t usSeat) { m_usSeat = usSeat; }
	inline bool IsAccept() const { return m_bAccept; }
	
	inline void SetAccept(bool bAccept) { m_bAccept = bAccept; }
	inline bool	IsDismissAccept() const { return m_bDismissAccept; }
	inline void SetDismissAccept(bool bAccept) { m_bDismissAccept = bAccept; }
	inline bool IsDisoverCard() const { return m_bDisoverCard; }
	inline void SetDisoverCard(bool bDisoverCard) { m_bDisoverCard = bDisoverCard; }
	inline bool IsPrepare() const { return m_bPrepare; }
	inline void SetPrepare(bool bPrepare) { m_bPrepare = bPrepare; }
	inline bool IsSanZhanged() const { return m_bSanZhang; }
	inline void SetSanZhang(bool bSanZhang) { m_bSanZhang = bSanZhang; }
	inline bool IsDingQueed() const { return m_bDingQue; }
	inline void SetDingQue(bool bDingQue) { m_bDingQue = bDingQue; }
	inline bool IsEnterRoomReady() const { return m_bEnterRoomReady; }
	inline void SetEnterRoomReady(bool bReady) { m_bEnterRoomReady = bReady; }
	inline bool IsReconectOtherReady() const { return m_bReconectOtherReady; }
	inline void SetReconectOtherReady(bool bReady) { m_bReconectOtherReady = bReady; }

	inline int32_t GetTotalFan() const { return m_nTotalFan; }
	inline void AddTotalFan(int32_t nFan) { m_nTotalFan += nFan; }
	inline void UpdateTotalFanAll() { m_nTotaFanAll += m_nTotalFan;}
	inline uint32_t GetTotalFanAll() const { return m_nTotaFanAll; }
	inline uint16_t GetZiMoTimesAll() const { return m_usZiMoTimesAll; }
	inline uint16_t GetDianPaoTimesAll() const { return m_usDianPaoTimesAll; }
	inline uint16_t GetAnGangTimesAll() const { return m_usAnGangTimesAll; }
	inline uint16_t GetMingGangTimesAll() const { return m_usMingGangTimesAll; }
	inline uint16_t GetNextGangTimesAll() const { return m_usNextGangTimesAll; }
	inline uint16_t GetTotalGangTimes() const { return m_usAnGangTimesAll + m_usMingGangTimesAll + m_usNextGangTimesAll; }
	inline uint16_t GetHitTotal() const { return m_usHitMaTotal; }
	inline uint16_t GetHuPaiTotal() const { return m_usHuPaiTotal; }
	inline bool IsBigWin() const { return m_bBigWin; }
	inline void SetBigWin() { m_bBigWin = true; }

	bool CheckNextGang(uint16_t usPai) const;

	inline uint16_t GetMingGangTimes() const { return m_usFanMingGang;}
	inline uint16_t GetAnGangTimes() const { return m_usFanAnGang;}
	inline uint16_t GetNextGangTimes() const { return m_usFanNextGang;}
	inline void AddNextGangTimes() { ++m_usFanNextGang; }
	inline uint16_t GetFangGangTimesThisInn() const { return m_usFangGangTimes; }
	inline void AddFangGangTimesThisInn(uint16_t usTimes) { m_usFangGangTimes++; }

	inline void AddZiMoTimes(uint16_t usTimes,bool isGhostHu = false) 
	{
		if (isGhostHu)
			m_usGhostZiMoTimesAll += usTimes;
		else
			m_usZiMoTimesAll += usTimes;
	}
	inline void AddDianPaoTimes(uint16_t usTimes) { m_usDianPaoTimesAll += usTimes; }
	inline void AddAnGangTimes(uint16_t usTimes) { m_usAnGangTimesAll += usTimes; }
	inline void AddMingGangTimes(uint16_t usTimes) { m_usMingGangTimesAll += usTimes; }
	inline void AddNextGangTimes(uint16_t usTimes) { m_usNextGangTimesAll += usTimes; }
	inline void AddFangGangTimes(uint16_t usTimes) { m_usFangGangTimesAll += usTimes; }
	inline void AddHitMaTotal(uint16_t usTimes) { m_usHitMaTotal += usTimes; }
	inline void AddHuPaiTotal(uint16_t usTimes) { m_usHuPaiTotal += usTimes; }

	inline void SetLastQuickMessTime(time_t nowTime) { m_LastQuickMessTime = nowTime; };
	inline time_t GetLastQuickMessTime() const { return m_LastQuickMessTime; }

	bool IsBlocking();

public:

	uint64_t		m_unSessionID;		//����SessionID
	uint32_t		m_unFepServerID;	//���ط�����ID
	uint64_t		m_ulCharID;			//��ɫID
	std::string		m_strAccount;		//�˺�
	std::string		m_strCharName;		//��ɫ��
	int32_t			m_nLevel;			//��ҵȼ�
	std::string		m_strLogoIcon;		//ͷ��
	int32_t			m_nTitle;			//�ƺ�
	int32_t			m_nDiamond;			//��ʯ
	int32_t			m_nCoin;			//���������ӵ�����
	uint16_t		m_usSexual;			//�Ա�

	int32_t			m_nRoomCards;		//������
	int32_t			m_nTotalGames;		//�ܾ���
	int32_t			m_nWinGames;		//ʤ������
	int32_t			m_nConGames;		//��ʤ����(��ǰ)
	int32_t			m_nHisConGames;		//�����ʤ����
	int32_t			m_nHisMaxScore;		//��ʷ��߷�
	int32_t			m_nWeekMaxScore;	//������߷�
	uint32_t		m_usTodayPlayNum;	//������ɵĴ��������ƽ�ɢ��
	std::string		m_strReadname;
	std::string		m_strReadcard;

	time_t			m_usLoginTime;		//��¼ʱ��
	time_t			m_usLastGameEnd;	//�Ͼֽ���ʱ��

	uint64_t		m_ulResetTime;			//����ʱ��
	uint32_t		m_unFirstShowStatus;	//�״η���״̬ 0:δ���� 1:�ѷ��� 2:����ȡ����
	uint32_t		m_unHasInvFriendNum;	//�ѳɹ�������ѵ�����
	uint32_t		m_unHasGetRoomCard;		//�ѳɹ���ȡ����������
	uint32_t		m_unCanGetRoomCard;		//��������ȡ����������
	uint32_t		m_unBeInvitationID;		//�����룬���������˵�ID
	std::string		m_strBeInvitationName;  //����������
	uint32_t		m_unPlayGames;			//����ľ���
	uint32_t		m_unRecvRewardStatus;	//��ȡ����״̬��0��������ȡ 1������ȡ 2������ȡ��
	uint32_t		m_usTodayPlayStatus1;	//��ȡ��״̬����10��
	uint32_t		m_usTodayPlayStatus2;	//��ȡ��״̬����20��


	bool			m_bDirtyData;		//������

public:

	// ��һ�ΰ�����
	uint16_t m_nLastAnPai;
	uint16_t m_nLastAnFromPos;
	uint16_t m_nLastAnTime;

	// ��һ�����ܵ���
	uint16_t m_nLastMingPai;
	uint16_t m_nLastMingFromPos;
	uint16_t m_nLastMingTime;

	// ��һ�ι��ָܵ���
	uint16_t m_nLastGuoShouPai;
	uint16_t m_nLastGuoShouFromPos;
	uint16_t m_nLastGuoShouTime;

	// ��һ��������
	uint16_t m_nLastPengPai;
	uint16_t m_nLastPengFromPos;
	uint16_t m_nLastPengTime;

	// 258��������
	bool m_b258ZuoJiangJiaFan;
	bool m_bHuPaiHu258;
	bool m_bQysJiaFan;

public:
	
	void AddRoomCards(int32_t num, ::fogs::proto::msg::log_type type);
	bool SubRoomCards(int32_t num,::fogs::proto::msg::log_type type,int32_t game_type = 0,int32_t record_id = 0);

	//void RecordMoneyEvent//LOG();

	void OnChangeWins();
	void OnChangeScore();

	int32_t GetTopWinsTotal();
	int32_t GetTopScoreTotal();

	inline void SetTopWinSort(int32_t nTopWinSort) { m_nTopWinSort = nTopWinSort; }
	inline void SetTopScoreSort(int32_t nTopScoreSort) { m_nTopScoreSort = nTopScoreSort; }
	inline int32_t GetTopWinSort() const { return m_nTopWinSort; }
	inline int32_t GetTopScoreSort() const { return m_nTopScoreSort; }

	// 
	inline void SetTopWinsTotal(int32_t nTopWinScore) { m_nTopWinsTotal = nTopWinScore; SetDirtyData(); }
	inline void SetTopScoreTotal(int32_t nTopScoreTotal) { m_nTopScoreTotal = nTopScoreTotal; SetDirtyData(); }

	inline void SetGpsInfo(const stGpsInfo& info){m_stGpsInfo = info;}
	inline const stGpsInfo& GetGpsInfo() const { return m_stGpsInfo; }
	inline void SetBlockTime(uint64_t _time) { m_bBlockTimeEnd = _time; }
	inline uint64_t GetBlockTime()  const { return m_bBlockTimeEnd; }
	inline void SetIsRobotPlaying(bool _bVal) { m_bIsRobotPlaying = _bVal; }
	inline uint16_t GetAddMaPai() const { return m_usAddMaPai; }
	inline void SetJiangGhostNum(uint16_t usJiangGhostNum) { m_usJiangGhostNum = usJiangGhostNum; }
	inline uint16_t GetJiangGhostNum() const { return m_usJiangGhostNum; }
	inline void SetInnWuHuaJiaBei(bool _jiaBei) { m_bInnWuHuaJiaBei = _jiaBei; }
	inline bool GetInnWuHuaJiaBei() const { return m_bInnWuHuaJiaBei; }

	inline bool IsRobot() const { return m_ulCharID >= ROBOT_START_ID && m_ulCharID <= ROBOT_END_ID; }
	void StartRobot();
	void CancelRobot();

	void SyncToWs();

	void AddEnterRoomOtherMsg(uint16_t usCmd, uint16_t usCCmd, const google::protobuf::Message& proData);
	void SendEnterRoomOtherMsg();

private:

	// �����ս��ͳ�Ƽ���
	time_t			m_nTopWinYmd;			//���а�ͳ�Ƽ�¼ʱ�������
	int32_t			m_nTopWinsTotal;		//��ǰʤ������
	time_t			m_nTopScoreYmd;			//���а�ͳ�Ƽ�¼ʱ�������
	int32_t         m_nTopScoreTotal;		//��ǰ��û���
	std::string		m_strIP;				//IP
	int32_t			m_nTopWinSort;			//��ʱ��ʤ����
	int32_t			m_nTopScoreSort;		//��ʱ��������

private:

	uint32_t		m_unRoomID;			//����ID
	uint16_t		m_usSeat;			//��λ��

	//����
	std::vector<uint16_t> m_vecPai;		//��
	std::vector<uint16_t> m_vecDicardPai;//������
	vecEventPai		m_vecEventPai;		//�¼���
	std::vector<uint16_t> m_vecHitMa;	//����
	std::vector<uint16_t> m_vecPengSeat;//���Ƶ�λ��
	bool			m_bAccept;			//�ͻ��˽��ܷ�����ʼ����
	bool			m_bDismissAccept;	//��ɢ�������
	bool			m_bDisoverCard;		//�Ƿ������
	bool			m_bPrepare;			//׼��
	bool			m_bSanZhang;		//׼��������
	bool			m_bDingQue;			//׼����ȱ��
	bool			m_bEnterRoomReady;	//���뷿��׼����(��һ��ʱ��������������û��Ӱ��)
	bool			m_bReconectOtherReady;// ͬ����������ҵ�����
	std::vector<PbMsgWebSS>	m_vecEnterRoomOtherMsg;//���뷿���������ҵ���Ϣ����

	int32_t			m_nTotalFan;		//�ܷ���
	uint16_t		m_usFanMingGang;	//���ܷ���
	std::vector<uint16_t> m_vecFanMingGangSeated;// �����ܵ���;
	uint16_t		m_usFanAnGang;		//���ܷ���
	uint16_t		m_usFanNextGang;	//���ָܷ���
	uint16_t		m_usFangGangTimes;	//�ŸܵĴ���

	uint16_t		m_usJiangGhostNum;	//���������(��Ҫ�ж��ǲ���������)
	bool			m_bInnWuHuaJiaBei;	//�Ƿ��޻��ӱ�

	//��������
	int32_t			m_nTotaFanAll;			//�ܷ���(��������)	
	uint16_t		m_usZiMoTimesAll;		//��������
	uint16_t		m_usGhostZiMoTimesAll;	//�й�����
	uint16_t		m_usDianPaoTimesAll;	//���ڴ���
	uint16_t		m_usAnGangTimesAll;		//���ܴ���
	uint16_t		m_usMingGangTimesAll;	//���ܴ���
	uint16_t		m_usNextGangTimesAll;	//���ָܴ���
	uint16_t		m_usFangGangTimesAll;	//�Ÿܴ���
	uint16_t		m_usHitMaTotal;		//�����ܸ���
	uint16_t		m_usHuPaiTotal;		//�ܺ��Ĵ���
	
	bool			m_bBigWin;				//�Ƿ��Ӯ��
	bool			m_bDisconnect;			//�Ƿ����
	time_t			m_tDisconnectTime;		//����ʱ���

	uint16_t		m_usAddMaPai; // �Ƿ��м���

private:
	//
	time_t			m_LastQuickMessTime; // �ϴ�ʹ�ÿ��˵��ʱ��
	stGpsInfo		m_stGpsInfo;		// λ�û�����Ϣ 
	time_t			m_bBlockTimeEnd;	// �Ƿ񱻷�ס

	fogs::FogsTimer*	m_pRobotDataTimer;
	bool				m_bIsRobotPlaying;

										//
public:
	bool							m_bIsLinting;
	::msg_maj::TingPaiWaiteNotify	m_tingPaiNotify;
	::msg_maj::TingPaiDiscardNotify	m_tingPaiListNotify;

public:
	uint16_t GetHutimes() const;
	void GetHuTiles(std::vector<uint16_t>& vecHuTiles) const;
	void GetHuTimesVec(std::vector<stHuDetail>& vecHuDetail);
	bool IsHued() const;

	void AddScore(const stHuDetail& hu);
	void AddScore(const stFengYuDetail& fengyu);
	void AddScore(const stHuaZhuDetail& huazhu);
	void AddScore(const stDaJiaoDetail& dajiao);
	void AddScoreBackTax(int16_t backTax);
	void AddScoreHujzy(int16_t hujzy);
	int16_t GetLastGangScore();
	void AddGuoPengPai(int16_t usPai);
	void AddGuoGangPai(int16_t usPai);
	bool HasGuoGangPai(int16_t usPai);

public:
	// ѪսѪ��
	uint16_t					m_usDingQueType;	// ȱһ��
	bool						m_bIsHuaZhu;		// �Ƿ���
	bool						m_bIsNotTing;		// �Ƿ�û������
	uint16_t					m_usTingMaxFan;		// ���������
	std::vector<stScoreDetail>  m_vecScoreDetail;	// �Ʒ���ϸ
	std::vector<uint16_t>       m_vecSanZhang;		// ����
	uint16_t					m_usGuohuPai;		// ������״̬true��,false��
	std::set<uint16_t>			m_setGuoPengPai;	// ��������
	std::set<uint16_t>			m_setGuoGangPai;	// ���ܵ���

};

extern ::boost::object_pool<CPlayer> g_objpoolPlayer;

#endif
