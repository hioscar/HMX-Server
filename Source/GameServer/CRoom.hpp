#ifndef _CROOM_H_
#define _CROOM_H_
#include <boost/pool/object_pool.hpp>
#include "Global.hpp"
#include "CMaJiang.hpp"
#include "FogsTimerService.hpp"

class CPlayer;
class CMaJiang;
class CMajingRule;

enum eRoomStatus
{
	eRoomStatus_Ready		= 1, //׼��״̬
	eRoomStatus_ClickStart  = 2, //�����ʼ
	eRoomStatus_SanZhang	= 3, //������
	eRoomStatus_DingQue		= 4, //��ȱ��
	eRoomStatus_StartGame	= 5, //��ʼ״̬
	eRoomStatus_End			= 6, //����״̬
};

enum eRoomCloses
{
	eRoomCloses_Finish	= 0, // ������������С�ֽ�ɢ
	eRoomCloses_Hand	= 1, // �ֶ���ɢ
	eRoomCloses_TimeOut = 2, // ��ʱ��ɢ
	eRoomCloses_NotPersons = 3, // ���˽�ɢ
};

// ��������Ϣ
struct stOpenTile
{
	::msg_maj::event_type event_t;
	std::vector<int16_t> tile_list;
	stOpenTile()
	{
		event_t = ::msg_maj::e_none;
	}
};

// ������Ϣ
struct stHuInfo
{
	::msg_maj::hu_way	 hu_way;	// ���Ʒ�ʽ
	::msg_maj::hu_type	 hu_type;	// ��������
	std::vector<int16_t> ma_pai_all;// ���е�����
	std::vector<int16_t> ma_pai_hit;// �������
	uint32_t jiang_ghost_num; // ��������ʱ�����ƹ������(0:�޻򲻷��ϵ���,1:����1����,2:����2����)
	uint32_t jiejiegao_times; // �ڽڵڼ���
	bool wuGhostJiaBei;// �޹�ӱ�
	stHuInfo()
	{
		hu_way = ::msg_maj::hu_way_none;
		hu_type = ::msg_maj::hu_none;
		jiang_ghost_num = jiejiegao_times = 0;
		wuGhostJiaBei = false;
	}
};

// ÿһС�ֽ��
struct stGameResultSeat
{
	int16_t					seat;			// ��λ��
	int16_t					total_score;	// �÷�
	std::vector<int16_t>	hand_titles;	// ���е���
	std::vector<stOpenTile> open_titles;	// �����ܵ���
	int16_t					an_gang;		// ���ܵķ���
	int16_t					ming_gang;		// ���ܵķ���
	int16_t					guoshou_gang;	// ���ָܵķ���
	stHuInfo				hu_info;		// ������Ϣ
	int16_t					hu_tile;		// ������
	int16_t					dingque;		// ����
	std::vector<stScoreDetail>	score_detail;
	int16_t					game_type;		// ��Ϸ�淨
	stGameResultSeat()
	{
		seat = total_score = an_gang = ming_gang = guoshou_gang = hu_tile = dingque = game_type = 0;
	}
};

// ÿһ�δ��Ƶļ�¼
struct stReplayAction 
{
	::msg_maj::event_type	event_t;	//�¼�
	int16_t		actor_seat;		//����������
	int16_t		victim_seat;	//��������,��ʱ-1
	stHuInfo		hu_info;		//����Ǻ����ˣ���������Ϣ
	std::vector<int16_t> event_tile_list;//�¼��������Ƶ��б�
	int16_t		desk_tile_count;	// ʣ���Ƶ�����
	stReplayAction()
	{
		event_t = msg_maj::e_none;
		actor_seat = victim_seat = desk_tile_count = 0;
	}
};

// ��ʼ����
struct stSeatInfo
{
	int16_t seat;	// ��λ
	std::vector<int16_t> hand_tiles;	// ����
	std::vector<stOpenTile> open_tiles;	// �����ܵ���
	std::vector<int16_t> discard_tiles; // �������
	::msg_maj::player_status pstatus;	//���״̬
	int16_t score;		// ���������ַ���
	int16_t dingque;	// ����
	stSeatInfo()
	{
		seat = score = dingque = 0;
		pstatus = ::msg_maj::normal;
	}
};

// ÿһС�ֵ���Ϣ
struct stInnRecord
{
	int16_t						inn_id;		// ����ID
	int16_t						banker_seat;// ׯ����λ��
	int16_t						dice;		// ������
	std::vector<stSeatInfo>		seat_info;	// ��ʼ��
	std::vector<stGameResultSeat> seat_result;// ��λ����
	stInnRecord()
	{
		inn_id = banker_seat = dice = 0;
	}
};

// ÿһС�ֵĳ��Ƽ�¼
struct stInnReplay
{
	int16_t						inn_id;		// ����ID
	std::vector<stReplayAction>	replay_list;// �ط�����(���ƾ���)
	stInnReplay()
	{
		inn_id = 0;
	}
};


// ÿλѡ����Ϣ
struct stPlayerInfo
{
	int16_t seat;
	uint64_t uid;
	std::string nick;
	std::string actor_addr;
	stPlayerInfo()
	{
		uid = seat = 0;
	}
};

class CRoom
{
public:
	CRoom(::msg_maj::RoomType roomType, ::msg_maj::maj_type majType,const ::msg_maj::RoomOption& option);
	~CRoom();

	void Release();
	inline void SetRoomID(uint32_t usRoomID) { m_unRoomID = usRoomID; }
	inline uint32_t GetRoomID() const { return m_unRoomID; }
	inline void SetRoomer(uint64_t ulRoomer) { m_ulRoomer = ulRoomer; }
	inline uint64_t GetRoomer() const { return m_ulRoomer; }

	inline eRoomStatus GetRoomStatus() const { return m_eRoomStatus; }

	inline CMaJiang* GetMajiang() const { return m_pMaj; }

	inline uint16_t GetBankerSeat() const { return m_usBankerSeat; }

	inline CMajingRule* GetRule() const { return m_pRule; }

	inline int32_t GetMaxMultiNum() const { return m_nMaxMultiNum; }

	inline bool IsClose() const { return m_bClose; }

	inline bool IsXieZhanLiu() const { return (m_usGameType == ::msg_maj::maj_t_xiezhan || m_usGameType == ::msg_maj::maj_t_xieliu); }

	inline void SetTest() { m_bTest = true; }

	inline bool IsTest() const { return m_bTest; }

	inline const ::msg_maj::RoomOption& GetRoomOption() const { return m_roomOption; }
	inline void UpdateRoomOption(const ::msg_maj::RoomOption& _roomOption) { m_roomOption.CopyFrom(_roomOption); };

	inline ::msg_maj::maj_type GetMajType() const { return m_usGameType; }

	inline bool IsHaiDiLaoYue() const { return m_bHaiDiLaoYue; }
	inline bool IsRobot() const { return m_bRobot; }
	void StartRobotJoin();

public:

	bool EnterPlayer(CPlayer* pPlayer);

	void LeavePlayer(CPlayer* pPlayer);

	void SetLeaveData(uint16_t usSeat);

	void RoomStatusEvent(CPlayer* pPlayer, bool bDisconnect);

	void ReconnectPlayer(CPlayer* pPlayer);

	void DisconnectPlayer(CPlayer* pPlayer);

	bool IsDisconnectAll();

	CPlayer* GetPlayer(uint16_t usSeat) const;

	uint16_t GetCurPersons() const; //��ǰ����

	inline uint16_t GetTotalPersons() const { return m_usRoomPersons; } //������

	void SetToProto(::msg_maj::RoomInfo* pPro);

	void BrocastMsg(uint16_t usCmd, uint16_t usCCmd, const ::google::protobuf::Message& msg, CPlayer* pPlayer = NULL);

	void SendRoomInnInfo(CPlayer* pPlayer = NULL);

private:

	bool CheckStart();

	void SendStartButton();

	void SendCancelStartButton();

	void SendHandCards();  // ���ƣ����ڻ����š���ȱ

	void RecordHandTiles();	// ���ÿ�ʼ����¼�����Ϣ

	void SendAskSanZhang(CPlayer* pPlayer = NULL);

	void SendAskDingQue(CPlayer* pPlayer = NULL);

	void ExchangeSanZhangPai();

	void StartTimerSendCard();

	void StartTimerClose();

	void CancelTimerClose();

	void Close(int32_t reason);

	void SendCard();

	void BroadcastSendCard(::msg_maj::DealNotify proData);

	bool DisoverCardAll(); //�Ƿ�������ҷ������

	bool AcceptAskAll(); //�Ƿ�������Ҷ����տ�ʼ��Ϸ

	bool SanZhangAll();

	bool DingQueAll();

	bool DissmissAcceptAll(); //�Ƿ�������Ҷ�ͬ���ɢ

	bool PrepareRoundAll(); //�Ƿ�������Ҷ�׼������

	bool End(); //���ֽ���

	void EndAll(); //���ֽ���

	void DissmissRoom(int32_t reason); //��ɢ����

	void DelDiscardTile(); //ɾ���������
	
	void CountEventGang(uint16_t usSeat, uint16_t usEventType); // �����¼�����

	void ResetData(); //��������

	void ChangeBankerSeat(); //����ׯ��λ��

	uint32_t GetDissmissRoomProtectTime();

	void SendNotifyGhostPaiListResult(CPlayer* pPlayer, bool is_disconn = false);

public:

	//����������¼�
	void HandleEventMultiple(CPlayer* pPlayer, uint16_t usEventType, uint16_t usParam);

	//����������¼�
	void HandleEventSingle(CPlayer* pPlayer, uint16_t usEventType, uint16_t usParam);

public:
	// �ͻ��˿�ʼ��Ϸ����
	void StartGameReq(CPlayer* pPlayer);
	// �ͻ��˽��ܷ�����ʼ����
	void AcceptAskReq(CPlayer* pPlayer, bool bAccept);
	// ѡ������
	void SanZhangReq(CPlayer* pPlayer,std::vector<uint16_t>& vecSanZhang);
	// ѡ��һ��
	void DingQuiReq(CPlayer* pPlayer,uint16_t usLessType);
	// ���ÿ�ʼ����
	bool CheckAndCostRoomCard();

	void RecordPlayerInfo();

	void SendDingQueNotify(CPlayer* pPlayer = NULL);

	// �ͻ��˴���
	void DiscardTileReq(CPlayer* pPlayer, uint16_t usPai);

	// �ͻ��˲����¼�(�����ܡ�������)
	void ResponseEventReq(CPlayer* pPlayer, uint16_t usEventType, uint16_t usParam);
	// �ͻ��˷�������ϱ�
	void DisoverCardReq(CPlayer* pPlayer);
	// �ͻ��˽�ɢ��������
	void DissmissRoomReq(CPlayer* pPlayer);
	// ��ɢ����ͬ�����
	void DissmissAcceptReq(CPlayer* pPlayer, bool bAccept);
	// �ͻ���׼��(��һ��)
	void PrepareRoundReq(CPlayer* pPlayer);
	// ���׼���׶ε�״̬
	void PreparRoundCheck(CPlayer* pPlayer);
	// �ͻ����������سɹ�
	void ReconnectReadyReq(CPlayer* pPlayer);
	void ReconnectOtherReadyReq(CPlayer* pPlayer);
	// ���������
	void KickRoleReq(CPlayer* pPlayer, uint16_t usSeat);
	// ���뷿��׼��������
	void EnterRoomReadyReq(CPlayer* pPlayer);
	// ���뷿�������������׼����
	void ReconectOtherReadyReq(CPlayer* pPlayer);

private:

	bool m_bTest;

	::msg_maj::maj_type		m_usGameType;		//��Ϸ���� ���縧���齫
	::msg_maj::RoomType		m_eRoomType;		//��������	
	uint32_t m_unRoomID;					//����ID
	uint64_t m_ulRoomer;					//����

	::msg_maj::RoomOption	m_roomOption;	// ��������

	uint64_t m_ulRoomUUID;					//����ΨһID
	eRoomStatus m_eRoomStatus;				//����״̬
	std::vector<CPlayer*> m_vecPlayer;		//�������
	int32_t m_nAllGames;					//�ܾ���
	int32_t m_nGames;						//����

	int32_t m_usMaxMultiType;				//��߷����� 0:���ⶥ 1:20 2:80
	int32_t m_nMaxMultiNum;					//��߷�����

	bool m_bHaiDiLaoYue;

	bool m_bStart;							//�Ƿ��ǵ����ʼ��Ϸ֮����Ϸ��ʼ
	bool m_bClickDissmiss;					//�Ƿ�����ɢ
	bool m_bClose;							//�Ƿ�ر�
	uint16_t m_usRoomPersons;				//��������

	fogs::FogsTimer* m_pTimerSendCard;		//���ƶ�ʱ��
	fogs::FogsTimer* m_pTimerClose;			//�رն�ʱ��
	CMaJiang* m_pMaj;						//�齫����
	CMajingRule* m_pRule;					//�齫����
	uint16_t m_usBankerSeat;				//ׯ��λ��

	bool m_bRobot;							//�Ƿ�����������
	int32_t m_usLimitTime;					//�Ƿ���ʱ������(ʱ�䵽��Զ���ɢ)
	
public:

	/*
	 * ��¼������Ϣ
	 * �ڿ�ʼ��Ϸʱ��¼
	 */
	void AddRoomInfo(uint64_t record_id,uint32_t nRoomID,int16_t room_type, const ::msg_maj::RoomOption& room_option, time_t startTime);

	/*
	 ��¼�����Ϣ
	 �ڴ������俪ʼʱҪ��¼
	 */
	void AddPlayerInfo(const std::vector<stPlayerInfo>& infos);

	/*
	���ֱ���Ҫ�ȵ���һ�θýӿ�
	inn_id;		 ����ID
	banker_seat; ׯ����λ��
	dice;		 ������
	*/
	void AddInnRecord(int16_t inn_id,int16_t banker_seat,int16_t dice);

	/*
	 �����ƺ󣬼�¼ÿ����ҵĳ�ʼ��
	 seatInfos :��λ��Ϣ
	 */
	void AddSeatInfo(int16_t inn_id, const std::vector<stSeatInfo>& seatInfos);

	/*
	ÿ���ƵĶ�����¼
	*/
	void AddReplayAction(int16_t inn_id,const stReplayAction& replay);

	/*
	��������ʱ���ã�����ÿ����λ�ϵ���Ϣ
	seat_result 4������λ����ʱ����
	*/ 
	void AddGameResult(int16_t inn_id,const std::vector<stGameResultSeat>& seat_result,bool isDissovle = false);

	/*
	 * ������Ϣ 
	 */
	bool GetRoomInfo(::msg_maj::RoomInfo& roomInfo);

	/*
	 * ��ý�ɫ��Ϣ
	 */
	bool GetRoleInfoList(::msg_maj::RoleInfoListS& roomInfo);

	/*
	 * ��õ��ּ�¼
	 */
	bool GetInnRecordS(int16_t inn_id, ::msg_maj::InnRecordS& innRecord);

	/*
	 * ������м�¼
	 */
	void GetInnRecordListS(::msg_maj::InnRecordListS* innRecordListS);

	/*
	 * ��õ��ֻط�
	 */
	bool GetInnReplayS(int16_t inn_id, ::msg_maj::InnReplayActionS& innReplay);

	 /*
	 * ������лط�
	 */
	void GetInnReplayS(std::map<int16_t, ::msg_maj::InnReplayActionS>& mapInnReplay);

	/*
	 * �����λ�ϵ����� 
	 */
	bool GetInnRecordSeatInfo(int16_t inn_id,std::map<uint16_t, stGameResultSeat>& mapSeat);

	/*
	 * ������Ϸ��־��¼
	 */
	void AddRecordToLog(const ::msg_maj::RoomInfo& roomInfo,const ::msg_maj::RoleInfoListS& roleInfo, const ::msg_maj::InnRecordS& innRecordS);

	/*
	 * 
	 */
	void GetAllInnRecordSeatScore(std::map<uint16_t, int16_t>& mapSeatScore);

	/*
	 * ���ս��ΨһID
	 */
	inline uint64_t GetRecordID() const { return m_unRecordID; }

	/*
	* ���ս��ʱ��
	*/
	inline uint64_t GetZjStartTime() const { return m_reconrdTime;}

	void RecordInnZhanJiLocal(bool isDissolve = false);
	void SaveInnZhangJiGamedb();
	// ��װ���Ƽ��� 
	void GetCopyPaiList(std::vector<uint16_t>& pailist_copy, CPlayer* pPlayer, uint16_t usPai);
private:

	uint64_t						m_unRecordID;		// ��¼ID
	uint32_t						m_unZjRoomID;		// �����
	time_t							m_reconrdTime;		// ����ʱ��
	time_t							m_startTime;		// ��ʼʱ��
	int16_t							m_nRoomType;		// ��������
	::msg_maj::RoomOption			m_roomZjOption;		// ��������
	std::map<int16_t, stPlayerInfo>	m_mapPlayerInfos;	// ѡ����Ϣ
	std::map<int16_t, stInnRecord>	m_mapInnRecords;	// ս�߼�¼
	std::map<int16_t, stInnReplay>  m_mapInnReplays;	// �ؿ���¼

public:

	void GetTingPaiData(CPlayer* pPlayer, std::vector< ::msg_maj::PromptPai>& vecPromptPai, const std::vector<uint16_t>& pailist_copy);
	void TingPaiDiscardPai(CPlayer* pPlayer);
	void TingPaiWaitePai(CPlayer* pPlayer,bool bTurnMe);

	uint16_t GetHuPlayerCount() const; // �Ѿ���������
	void FillHuTimesToDetail(const stScoreDetail& huDetail, ::msg_maj::ScoreDetail* pHuDetail);
	void GetReconnResp(CPlayer* pPlayer, ::msg_maj::ReconnectLoadResp& proMaj);
	void ReconnectRobot(CPlayer* pPlayer);

};

extern 	::boost::object_pool<CRoom>	g_objpoolRoom;

#endif // !_CROOM_H_
