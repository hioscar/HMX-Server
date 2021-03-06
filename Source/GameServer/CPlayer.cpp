#include "CPlayer.hpp"

#include "CRoom.hpp"
#include "CRoomMgr.hpp"

#include "CNoticeMgr.hpp"
#include "CWorld.hpp"
#include "CMailMgr.hpp"
#include "CommFun.h"
#include "COnlineRecord.h"
#include "GameService.h"

::boost::object_pool<CPlayer> g_objpoolPlayer;

CPlayer::CPlayer(uint64_t unSessionID,uint32_t unFepServerID, const ::msg_maj::Role& proData) :
	m_unSessionID(unSessionID),
	m_unFepServerID(unFepServerID),
	m_ulCharID(proData.id()),
	m_strAccount(proData.account()),
	m_strCharName(proData.nickname()),
	m_nLevel(proData.level()),
	m_strLogoIcon(proData.logo_icon()),
	m_nTitle(proData.title()),
	m_nDiamond(proData.diamond()),
	m_nCoin(proData.coin()),
	m_usSexual(proData.sexual()),
	m_nRoomCards(proData.room_card()),
	m_nTotalGames(proData.total_games()),
	m_nWinGames(proData.win_games()),
	m_nConGames(proData.con_games()),
	m_nHisConGames(proData.his_max_con()),
	m_nHisMaxScore(proData.his_max_score()),
	m_nWeekMaxScore(proData.week_max_score()),
	m_usTodayPlayNum(proData.today_play_num()),
	m_strReadname(proData.readname()),
	m_strReadcard(proData.readcard()),
	m_usLoginTime(time(NULL)),
	m_usLastGameEnd(proData.last_game_end()),
	m_ulResetTime(proData.data().reset_time()),
	m_unFirstShowStatus(proData.data().first_show_status()),
	m_unHasInvFriendNum(proData.data().has_inv_friend_num()),
	m_unHasGetRoomCard(proData.data().has_get_room_card()),
	m_unCanGetRoomCard(proData.data().can_get_room_card()),
	m_unBeInvitationID(proData.data().be_invitation_id()),
	m_unPlayGames(proData.data().play_games()),
	m_unRecvRewardStatus(proData.data().recv_reward_status()),
	m_bDirtyData(false),
	m_nLastAnPai(0),
	m_nLastAnFromPos(100),
	m_nLastAnTime(0),
	m_nLastMingPai(0),
	m_nLastMingFromPos(100),
	m_nLastMingTime(0),
	m_nLastGuoShouPai(0),
	m_nLastGuoShouFromPos(100),
	m_nLastGuoShouTime(0),
	m_nLastPengPai(0),
	m_nLastPengFromPos(100),
	m_nLastPengTime(0),
	m_b258ZuoJiangJiaFan(false),
	m_bHuPaiHu258(false),
	m_bQysJiaFan(false),
	m_nTopWinYmd(proData.top_wins_ymd()),
	m_nTopWinsTotal(proData.top_wins_total()),
	m_nTopScoreYmd(proData.top_score_ymd()),
	m_nTopScoreTotal(proData.top_score_total()),
	m_strIP(proData.ip()),
	m_nTopWinSort(0),
	m_nTopScoreSort(0),
	m_unRoomID(0),
	m_usSeat(100),
	m_bAccept(false),
	m_bDismissAccept(false),
	m_bDisoverCard(false),
	m_bPrepare(false),
	m_bSanZhang(false),
	m_bDingQue(false),
	m_bEnterRoomReady(false),
	m_bReconectOtherReady(true),
	m_nTotalFan(0),
	m_usFanMingGang(0),
	m_usFanAnGang(0),
	m_usFanNextGang(0),
	m_usFangGangTimes(0),
	m_usJiangGhostNum(0),
	m_bInnWuHuaJiaBei(false),
	m_nTotaFanAll(0),
	m_usZiMoTimesAll(0),
	m_usGhostZiMoTimesAll(0),
	m_usDianPaoTimesAll(0),
	m_usAnGangTimesAll(0),
	m_usMingGangTimesAll(0),
	m_usNextGangTimesAll(0),
	m_usFangGangTimesAll(0),
	m_usHitMaTotal(0),
	m_usHuPaiTotal(0),
	m_bBigWin(false),
	m_bDisconnect(false),
	m_tDisconnectTime(0),
	m_usAddMaPai(0),
	m_LastQuickMessTime(0),
	m_bBlockTimeEnd(proData.blocktime()),
	m_pRobotDataTimer(NULL),
	m_bIsRobotPlaying(false),
	m_usDingQueType(0),
	m_bIsHuaZhu(false),
	m_bIsNotTing(false),
	m_usGuohuPai(0)
{
	m_stGpsInfo.reset();
	if (m_strLogoIcon.length() == 0)
	{
		m_strLogoIcon = "";
	}

}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	RefreshData(false);

	return true;
}

void CPlayer::RefreshData(bool bBackground)
{
	time_t tCurTime = time(NULL);
	if (!bBackground && GetZeroByTimeStamp(m_ulResetTime) == GetZeroByTimeStamp(tCurTime))
	{
		return;
	}

	//不是同一天
	m_ulResetTime = tCurTime;
	m_unFirstShowStatus = 0;
	m_usTodayPlayStatus1 = 0;
	m_usTodayPlayStatus2 = 0;
	m_bDirtyData = true;
}

bool CPlayer::InitPlayer()
{
	if (!Init()) {
		return false;
	}
	m_nLevel = 1;
    return true;
}

void CPlayer::SendLoginMsg(bool bDisconnect)
{
	::msg_maj::LoginPlayerResp proLogin;
	proLogin.set_code(::msg_maj::SUCCESS);
	proLogin.set_is_reconnect(bDisconnect);
	SetRoleProto(proLogin.mutable_role());
	proLogin.set_srv_time(time(NULL));
	proLogin.set_is_free(CWorld::Instance()->IsFreeCard());

	SendMsgToClient(::comdef::msg_login, ::msg_maj::login_player_resp, proLogin);

	SendSyncActivityInfo();
}

void CPlayer::SendNotifyAnotherLogin()
{
	if (m_unSessionID > 0)
	{
		::msg_maj::NotifyAnotherLogin proData;
		SendMsgToClient(::comdef::msg_login, ::msg_maj::notify_another_login,proData);
	}
}

void CPlayer::SendSyncActivityInfo()
{
	if (m_unSessionID > 0)
	{
		::msg_maj::SyncActivityInfo proData;
		proData.set_share_status(m_unFirstShowStatus);
		proData.set_inv_can_get_room_card(m_unCanGetRoomCard);
		SendMsgToClient(::comdef::msg_activity, ::msg_maj::Sync_activity_info,proData);
	}
}

void CPlayer::SendRoleData(CPlayer* lookPlayer)
{
	lookPlayer = lookPlayer ? lookPlayer : this;
	::msg_maj::PlayerInfoResp sendProto;
	::msg_maj::RoleC* role = sendProto.mutable_role();
	if (role)
	{
		role->set_id(lookPlayer->GetCharID());
		role->set_nickname(lookPlayer->GetCharName());
		role->set_logo_icon(lookPlayer->GetLogoIcon());
		role->set_room_card(lookPlayer->GetRoomCard());
		role->set_total_games(lookPlayer->GetTotalGames());
		role->set_win_games(lookPlayer->GetWinGames());
		role->set_his_con_games(lookPlayer->GetHisConGame());
		role->set_his_max_score(lookPlayer->GetHisMaxScore());
		role->set_top_score_total(lookPlayer->GetTopScoreTotal());
		const stGpsInfo& gps = lookPlayer->GetGpsInfo();
		role->set_address(gps.isOk() ? gps.address: lookPlayer->m_strIP);
		
		SendMsgToClient(::comdef::msg_role, ::msg_maj::player_info_resp, sendProto);
	}
}

void CPlayer::SendRoomCards(CPlayer* lookPlayer)
{
	lookPlayer = lookPlayer ? lookPlayer : this;
	::msg_maj::UpdateRoleData proUpdate;
	proUpdate.mutable_room_card_data()->set_room_card(lookPlayer->GetRoomCard());
	SendMsgToClient(::comdef::msg_role, ::msg_maj::update_role_data, proUpdate);
}

// 创建房间
void CPlayer::CreateRoom()
{
	::msg_maj::OpenRoomReq proReq;

}

void CPlayer::JoinRoom(uint32_t room_id)
{
	CRoom* pRoom = CRoomMgr::Instance()->GetRoomByID(room_id);
	if (NULL == pRoom || pRoom->IsClose())
	{
		H::logger->error("加入的房间已经不存在");
		return;
	}

	if (pRoom->GetCurPersons() == pRoom->GetTotalPersons())
	{
		H::logger->error("加入的房间人数已经满");
		return;
	}

	if (pRoom->EnterPlayer(this))
	{
		this->SetIsRobotPlaying(true);
		this->SyncToWs();

		::msg_maj::EnterRoomResp proRep;
		proRep.set_code(msg_maj::EnterRoomResp::SUCCESS);
		proRep.set_self_seat(this->GetSeat());
		proRep.set_banker_seat(pRoom->GetBankerSeat());
		pRoom->SetToProto(proRep.mutable_info());
		this->SetRoleInfoProto(proRep.add_rolelist());
		this->SendMsgToClient(::comdef::msg_room, ::msg_maj::enter_room_resp, proRep);
	}
}

void CPlayer::SaveDataToDB(int32_t type)
{
	if (!m_bDirtyData)
	{
		return;
	}

	fogs::proto::msg::SavePlayerRequest proto;
	proto.set_type(type);
	SetRoleProto(proto.mutable_role_info());
	GameService::Instance()->SendToDp(::comdef::msg_ss,::msg_maj::SavePlayerDataReqID, proto);
	//////////LOG(INFO) << "CPlayer::SaveDataToDB()";

	m_bDirtyData = false;
}

bool CPlayer::EnterGame()
{
	//////////LOG(INFO) << "CPlayer::EnterGame(): " << m_strAccount;

	if (m_unRoomID <= 0)
	{
		SendLoginMsg(false);

		m_bDisconnect = false;
	}
	else
	{
		SendLoginMsg(true);

		if (!m_bDisconnect)
		{
			return false;
		}

		CRoom* pRoom = CRoomMgr::Instance()->GetRoomByID(m_unRoomID);
		if (pRoom)
		{
			CancelRobot();
			CWorld::Instance()->DelRobotByUid(GetCharID());
			if (m_bIsRobotPlaying)
			{
				::msg_maj::StopRobotReq stopRobot;
				stopRobot.set_uid(GetCharID());
				SendMsgToClient(::comdef::msg_maj, ::msg_maj::stop_robot_req, stopRobot);
			}
			pRoom->ReconnectPlayer(this);
		}
	}

	// 进入游戏后的数据初始化
	UpdateTopToRank(::msg_maj::rank_t_wins);
	UpdateTopToRank(::msg_maj::rank_t_score);
	CNoticeMgr::Instance()->SendNoticeList(this);
	CMailSysLogMgr::Instance()->OnlinePlayer(this->GetCharID());
	CMailMgr::Instance()->OnlinePlayer(this->GetCharID());
	return true;
}

void CPlayer::SetDirtyData()
{ 
	m_bDirtyData = true; 
	CWorld::Instance()->AddSavePlayer(m_ulCharID); 
}

bool CPlayer::Disconnect()
{
	if (m_unRoomID > 0)
	{
		m_bDisconnect = true;
		m_tDisconnectTime = time(NULL);
		SetReconectOtherReady(false);
		CRoom* pRoom = CRoomMgr::Instance()->GetRoomByID(m_unRoomID);
		if (pRoom)
		{
			pRoom->DisconnectPlayer(this);
		}
		else
		{
			m_unRoomID = 0;
		}
		return true;
	}

	return false;
}

bool CPlayer::LeaveGame()
{
	SaveDataToDB(1);
	CWorld::Instance()->DelSavePlayer(m_ulCharID);
	return true;
}

void CPlayer::LeaveRoomEx()
{
	ResetRoomData();
	ResetMajData();
}

void CPlayer::Share()
{
	++m_unHasInvFriendNum;
	m_unCanGetRoomCard += 2;
}

void CPlayer::SetRoleProto(::msg_maj::Role* pPro)
{
	if (NULL == pPro)
	{
		return;
	}

	pPro->set_id(m_ulCharID);
	pPro->set_account(m_strAccount);
	pPro->set_nickname(m_strCharName);
	pPro->set_level(m_nLevel);
	pPro->set_logo_icon(m_strLogoIcon);
	pPro->set_title(m_nTitle);
	pPro->set_diamond(m_nDiamond);
	pPro->set_coin(m_nCoin);
	pPro->set_sexual(m_usSexual);

	pPro->set_room_card(m_nRoomCards);
	pPro->set_total_games(m_nTotalGames);
	pPro->set_win_games(m_nWinGames);
	pPro->set_con_games(m_nConGames);
	pPro->set_his_max_score(m_nHisMaxScore);
	pPro->set_his_max_con(m_nHisConGames);
	pPro->set_week_max_score(m_nWeekMaxScore);
	pPro->set_top_wins_total(m_nTopWinsTotal);
	pPro->set_top_wins_ymd(m_nTopWinYmd);
	pPro->set_top_score_total(m_nTopScoreTotal);
	pPro->set_top_score_ymd(m_nTopScoreYmd);
	pPro->set_blocktime(m_bBlockTimeEnd);
	pPro->set_today_play_num(m_usTodayPlayNum);
	pPro->set_readname(m_strReadname);
	pPro->set_readcard(m_strReadcard);
	pPro->set_login_time(m_usLoginTime);
	pPro->set_ip(m_strIP);

	pPro->mutable_data()->set_reset_time(m_ulResetTime);
	pPro->mutable_data()->set_first_show_status(m_unFirstShowStatus);
	pPro->mutable_data()->set_has_inv_friend_num(m_unHasInvFriendNum);
	pPro->mutable_data()->set_has_get_room_card(m_unHasGetRoomCard);
	pPro->mutable_data()->set_can_get_room_card(m_unCanGetRoomCard);

	pPro->mutable_data()->set_be_invitation_id(m_unBeInvitationID);
	pPro->mutable_data()->set_play_games(m_unPlayGames);
	pPro->mutable_data()->set_recv_reward_status(m_unRecvRewardStatus);
}

void CPlayer::SetRoleInfoProto(msg_maj::RoleInfo* pPro)
{
	if (NULL == pPro)
	{
		return;
	}

	pPro->set_uid(m_ulCharID);
	pPro->set_nickname(m_strCharName);
	pPro->set_logo_icon(m_strLogoIcon);
	pPro->set_seat_id(m_usSeat);
	pPro->set_sexual(m_usSexual);
	if (m_bDisconnect)
	{
		pPro->set_status(::msg_maj::disconnect);
	}
	else
	{
		pPro->set_status(::msg_maj::normal);
	}
	pPro->set_score(m_nTotaFanAll);
}

void CPlayer::SetSeatInfoProto(::msg_maj::SeatInfo* pPro, bool bReconnect) const
{
	if (NULL == pPro)
	{
		return;
	}

	pPro->set_seat(m_usSeat);
	for (std::vector<uint16_t>::const_iterator iter = m_vecPai.begin(); iter != m_vecPai.end(); ++iter)
	{
		if (bReconnect)
		{
			pPro->add_hand_tiles(0);
		}
		else
		{
			pPro->add_hand_tiles(*iter);
		}
	}

	for (vecEventPai::const_iterator iter = m_vecEventPai.begin(); iter != m_vecEventPai.end(); ++iter)
	{
		const stEventPai& st = *iter;
		::msg_maj::OpenTile* pProOTile = pPro->add_open_tiles();
		pProOTile->set_type(::msg_maj::event_type(st.usEventType));
		uint16_t usNum = 0;
		if (st.usEventType == ::msg_maj::pong)
		{
			usNum = 3;
		}
		else
		{
			usNum = 4;
		}
		for (uint16_t i = 0; i < usNum; ++i)
		{
			pProOTile->add_tile_list(st.usPai);
		}
	}

	for (std::vector<uint16_t>::const_iterator iter = m_vecDicardPai.begin(); iter != m_vecDicardPai.end(); ++iter)
	{
		pPro->add_discard_tiles(*iter);
	}

	std::vector<uint16_t> huTiles;
	this->GetHuTiles(huTiles);
	for (std::vector<uint16_t>::const_iterator it3 = huTiles.begin(); it3 != huTiles.end(); ++it3)
	{
		pPro->add_hu_tiles(*it3);
	}

	if (m_bDisconnect)
	{
		pPro->set_pstatus(::msg_maj::disconnect);
	}
	else
	{
		pPro->set_pstatus(::msg_maj::normal);
	}
	pPro->set_score(m_nTotaFanAll);
}

void CPlayer::SetTotalResultProto(::msg_maj::TotalResultSeat* pPro)
{
	if (NULL == pPro)
	{
		return;
	}

	pPro->set_seat(m_usSeat);
	pPro->set_total_score(m_nTotaFanAll);
	pPro->set_big_win(m_bBigWin);
	pPro->set_zimo_cnt(m_usZiMoTimesAll);
	pPro->set_ghost_zimo_cnt(m_usGhostZiMoTimesAll);
	pPro->set_dianpao_cnt(m_usDianPaoTimesAll);
	pPro->set_angang_cnt(m_usAnGangTimesAll);
	pPro->set_minggang_cnt(m_usMingGangTimesAll);
	pPro->set_guoshougang_cnt(m_usNextGangTimesAll);
	pPro->set_total_gang_cnt(m_usAnGangTimesAll + m_usMingGangTimesAll + m_usNextGangTimesAll);
	pPro->set_fanggang_times(m_usFangGangTimesAll);
	pPro->set_hit_ma_cnt(m_usHitMaTotal);
	pPro->set_hu_total_cnt(m_usHuPaiTotal);
}

void CPlayer::SendMsgToClient(uint16_t usCmd, uint16_t usCCmd, const google::protobuf::Message& proData)
{
	zSession* pFep = GameService::Instance()->SessionMgr()->getFep(m_unFepServerID);
	if (pFep == NULL)
	{
		ASSERT(0);
		return;
	}
	pFep->sendMsgProto(usCmd, usCCmd, m_unSessionID, m_unFepServerID, proData);
}

void CPlayer::UpdateTopToRank(::msg_maj::rank_type rank_t)
{
	fogs::proto::msg::UpdateSaveRanks sendProto;
	sendProto.set_ranktype(rank_t);
	if (rank_t == ::msg_maj::rank_t_wins)
	{
		::msg_maj::WinsInfo* info = sendProto.mutable_winsinfo();
		info->set_uid(this->GetCharID());
		info->set_name(this->GetCharName());
		info->set_value(this->GetTopWinsTotal());
		info->set_sort(0);
		info->set_type(0);
		info->set_time(time(NULL));
		info->set_actor_addr(this->GetLogoIcon());
	}
	else if (rank_t == ::msg_maj::rank_t_score)
	{
		::msg_maj::ScoreInfo* info = sendProto.mutable_scoreinfo();
		info->set_uid(this->GetCharID());
		info->set_name(this->GetCharName());
		info->set_value(this->GetTopScoreTotal());
		info->set_sort(0);
		info->set_type(0);
		info->set_time(time(NULL));
		info->set_actor_addr(this->GetLogoIcon());
	}
	else
		return;

	GameService::Instance()->SendToWs(::comdef::msg_ss, ::msg_maj::UpdateRankRequestID, sendProto);

}

void CPlayer::UpdateToGate()
{
	::msg_maj::RoleFep roleFep;
	roleFep.set_id(this->GetCharID());
	roleFep.set_sessionid(this->GetSessionID());
	roleFep.set_serverid(GameService::Instance()->GetServerID());
	SendMsgToClient(::comdef::msg_ss, ::msg_maj::UpdateFepUserID, roleFep);
}

bool CPlayer::IsGhostHu(CMajingRule* pRule)
{
	bool isGhostHu = false;
	for (std::vector<uint16_t>::const_iterator itPai = m_vecPai.begin(); itPai != m_vecPai.end(); ++itPai)
	{
		if (pRule->IsGhost() && pRule->IsGhostCard(*itPai))
		{
			isGhostHu = true;
			break;
		}
	}
	return isGhostHu;
}

uint16_t CPlayer::GetSanZhangLessType()
{
	uint16_t typeArr[] = {0,0,0};
	for (std::vector<uint16_t>::iterator it = m_vecPai.begin(); it != m_vecPai.end(); ++it)
	{
		uint16_t usPai = *it;
		typeArr[usPai / 10 - 1] += 1;
	}

	uint16_t lessType = 0;
	uint16_t lessCount = 0;
	for (int i = 0; i < sizeof(typeArr) / sizeof(typeArr[0]); ++i)
	{
		if (typeArr[i] >= 3)
		{
			if (lessType == 0)
			{
				lessType = i + 1;
				lessCount = typeArr[i];
			}
			else
			{
				if (typeArr[i] < lessCount)
				{
					lessType = i + 1;
					lessCount = typeArr[i];
				}
			}
		}
	}
	return lessType;
}

uint16_t CPlayer::GetDingQueLessType()
{
	std::map<uint16_t, uint16_t> mapTypeNum;
	mapTypeNum.insert(std::make_pair(1, 0));
	mapTypeNum.insert(std::make_pair(2, 0));
	mapTypeNum.insert(std::make_pair(3, 0));
	for (std::vector<uint16_t>::iterator it = m_vecPai.begin(); it != m_vecPai.end(); ++it)
	{
		uint16_t usPai = *it;
		uint16_t usType = usPai / 10;
		mapTypeNum[usType] += 1;
	}

	uint16_t lessType = 0;
	uint16_t lessCount = 0;
	for (std::map<uint16_t, uint16_t>::const_iterator it2 = mapTypeNum.begin(); it2 != mapTypeNum.end(); ++it2)
	{
		if (lessType == 0)
		{
			lessType = it2->first;
			lessCount = it2->second;
		}
		else
		{
			if (it2->second < lessCount)
			{
				lessType = it2->first;
				lessCount = it2->second;
			}
		}
	}
	return lessType;
}

bool CPlayer::CheckPaiNum()
{
	if (m_vecPai.size() % 3 == 1)
	{
		return true;
	}

	//LOG(ERROR) << "CPlayer::CheckPaiNum(): size: " << m_vecPai.size();
	return false;
}

bool CPlayer::AddPai(uint16_t usPai)
{
	bool bFind = false;
	for (std::vector<uint16_t>::iterator iter = m_vecPai.begin(); iter != m_vecPai.end(); ++iter)
	{
		if ((*iter) > usPai)
		{
			m_vecPai.insert(iter, usPai);
			bFind = true;
			break;
		}
	}
	if (!bFind)
	{
		m_vecPai.push_back(usPai);
	}

	return true;
}

bool CPlayer::DiscardTile(uint16_t usPai)
{
	if (DelPai(usPai))
	{
		m_vecDicardPai.push_back(usPai);
		return true;
	}

	return false;
}

void CPlayer::ResetRoomData()
{
	m_unRoomID = 0;
	m_usSeat = 100;
	m_bEnterRoomReady = false;
	m_bReconectOtherReady = true;
	m_nTotaFanAll = 0;
	m_bBigWin = false;
	m_usZiMoTimesAll = 0;
	m_usGhostZiMoTimesAll = 0;
	m_usDianPaoTimesAll = 0;
	m_usAnGangTimesAll = 0;
	m_usMingGangTimesAll = 0;
	m_usNextGangTimesAll = 0;
	m_usFangGangTimesAll = 0;
	m_usHitMaTotal = 0;
	m_usHuPaiTotal = 0;
}

void CPlayer::ResetMajData()
{
	m_vecPai.clear();
	m_vecDicardPai.clear();
	m_vecEventPai.clear();
	m_vecHitMa.clear();
	m_vecPengSeat.clear();

	m_bAccept = false;
	m_bDismissAccept = false;
	m_bDisoverCard = false;
	m_bPrepare = false;

	m_nTotalFan = 0;
	m_usFanMingGang = 0;
	m_usFanAnGang = 0;
	m_usFanNextGang = 0;
	m_usAddMaPai = 0;
	m_usFangGangTimes = 0;
	m_vecFanMingGangSeated.clear();
	m_usJiangGhostNum = 0;
	m_bInnWuHuaJiaBei = false;

	m_nLastAnPai = 0;
	m_nLastAnFromPos = 100;
	m_nLastAnTime = 0;
	m_nLastMingPai = 0;
	m_nLastMingFromPos = 100;
	m_nLastMingTime = 0;
	m_nLastGuoShouPai = 0;
	m_nLastGuoShouFromPos = 100;
	m_nLastGuoShouTime = 0;
	m_nLastPengPai = 0;
	m_nLastPengFromPos = 100;
	m_nLastPengTime = 100;
	m_b258ZuoJiangJiaFan = false;
	m_bHuPaiHu258 = false;
	m_bQysJiaFan = false;
	m_usDingQueType = 0;
	m_bIsHuaZhu = false;
	m_bIsNotTing = false;
	m_usTingMaxFan = 0;
	m_bSanZhang = false;
	m_bDingQue = false;
	m_vecScoreDetail.clear();
	m_vecSanZhang.clear();
	m_usGuohuPai = 0;
	m_setGuoPengPai.clear();
}

bool CPlayer::DelPai(uint16_t usPai)
{
	for (std::vector<uint16_t>::iterator iter = m_vecPai.begin(); iter != m_vecPai.end(); ++iter)
	{
		if (*iter == usPai)
		{
			m_vecPai.erase(iter);
			return true;
		}
	}

	//LOG(ERROR) << "CPlayer::DelPai() pai: " << usPai;
	return false;
}

bool CPlayer::PengPai(uint16_t usPai)
{
	for (uint16_t i = 0; i < 2; ++i)
	{
		if (!DelPai(usPai))
		{
			return false;
		}
	}

	AddEventPai(::msg_maj::pong, usPai);
	return true;
}

bool CPlayer::MingGang(uint16_t usPai)
{
	for (uint16_t i = 0; i < 3; ++i)
	{
		if (!DelPai(usPai))
		{
			return false;
		}
	}

	AddEventPai(::msg_maj::ming_gang, usPai);
	++m_usFanMingGang;
	return true;
}

void CPlayer::MingGangSeated(uint16_t usSeat)
{
	m_vecFanMingGangSeated.push_back(usSeat);
}

bool CPlayer::AnGang(uint16_t usPai)
{
	for (uint16_t i = 0; i < 4; ++i)
	{
		if (!DelPai(usPai))
		{
			return false;
		}
	}

	AddEventPai(::msg_maj::an_gang, usPai);
	++m_usFanAnGang;
	return true;
}

bool CPlayer::NextGang(uint16_t usPai, bool bEvent)
{
	if (!DelPai(usPai))
	{
		return false;
	}

	DelEventPai(::msg_maj::pong, usPai);
	AddEventPai(::msg_maj::guo_shou_gang, usPai);

	if (!bEvent)
	{
		++m_usFanNextGang;
	}

	return true;
}

void CPlayer::AddEventPai(uint16_t usType, uint16_t usPai)
{
	stEventPai st;
	st.usEventType = usType;
	st.usPai = usPai;
	m_vecEventPai.push_back(st);
}

void CPlayer::DelEventPai(uint16_t usType, uint16_t usPai)
{
	for (vecEventPai::iterator iter = m_vecEventPai.begin(); iter != m_vecEventPai.end(); ++iter)
	{
		if ((*iter).usEventType == usType && (*iter).usPai == usPai)
		{
			m_vecEventPai.erase(iter);
			break;
		}
	}
}

void CPlayer::DelDiscardPai(uint16_t usPai)
{
	if (m_vecDicardPai.size() <= 0)
	{
		return;
	}

	if (*m_vecDicardPai.rbegin() == usPai)
	{
		m_vecDicardPai.pop_back();
	}
}

void CPlayer::AddTodayPlayNum(int32_t num)
{
	m_usTodayPlayNum += num;

	bool bHadChanges = false;
	if (m_usTodayPlayStatus1 == 0 && m_usTodayPlayNum >= 10)
	{
		m_usTodayPlayStatus1 = 1; bHadChanges = true;
	}
	
	if (m_usTodayPlayStatus2 == 0 && m_usTodayPlayNum >= 20)
	{
		m_usTodayPlayStatus2 = 1; bHadChanges = true;
	}

	if (bHadChanges)
	{

	}

}


bool CPlayer::CheckNextGang(uint16_t usPai) const
{
	for (vecEventPai::const_iterator iter = m_vecEventPai.begin(); iter != m_vecEventPai.end(); ++iter)
	{
		if ((*iter).usEventType == ::msg_maj::pong && (*iter).usPai == usPai)
		{
			return true;
		}
	}

	return false;
}

void CPlayer::AddRoomCards(int32_t num, ::fogs::proto::msg::log_type type)
{
	if (num < 1)
		return;

	if (num + m_nRoomCards < 1) // 溢出
		return;

	SetRoomCard(m_nRoomCards + num);

	CWorld::Instance()->SendMoneyLog(GetCharID(),GetCharName(), num, GetRoomCard(),type);

	SaveDataToDB(2);

}

bool CPlayer::SubRoomCards(int32_t num, ::fogs::proto::msg::log_type type, int32_t game_type, int32_t record_id)
{
	if (num < 1)
		return false;

	if (m_nRoomCards < num  ) 
		return false;

	SetRoomCard(m_nRoomCards - num);

	CWorld::Instance()->SendMoneyLog(GetCharID(), GetCharName(), -num, GetRoomCard(), type);

	SyncToWs();
	SaveDataToDB(2);

	return true;
}

void CPlayer::OnChangeWins()
{
	UpdateTopToRank(::msg_maj::rank_t_wins);
}

void CPlayer::OnChangeScore()
{
	UpdateTopToRank(::msg_maj::rank_t_score);
}

int32_t CPlayer::GetTopWinsTotal()
{
	time_t limitDayTime = GetTurnYmd();
	if(m_nTopWinYmd == 0 || limitDayTime > m_nTopWinYmd)
	{
		m_nTopWinYmd = limitDayTime;
		m_nTopWinsTotal = 0;

		SetDirtyData();
	}
	return m_nTopWinsTotal;
}

int32_t CPlayer::GetTopScoreTotal()
{
	time_t limitDayTime = GetTurnYmd();
	if (m_nTopScoreYmd == 0 || limitDayTime > m_nTopScoreYmd)
	{
		m_nTopScoreYmd = limitDayTime;
		m_nTopScoreTotal = 0;

		SetDirtyData();
	}
	return m_nTopScoreTotal;
}

bool CPlayer::IsBlocking()
{
	return m_bBlockTimeEnd >= time(NULL);
}

void CPlayer::StartRobot()
{
	::msg_maj::StartRobotReq startRobot;
	startRobot.set_session_id(this->GetSessionID());
	startRobot.set_uid(this->GetCharID());
	this->SendMsgToClient(::comdef::msg_room, ::msg_maj::start_robot_req, startRobot);

	if (IsRobot())
	{
		CWorld::Instance()->AddRobot(this);
	}
	else // 机器人帮忙托管
	{
		// 发送当前的牌
	}
}

void CPlayer::CancelRobot()
{
	if (m_pRobotDataTimer)
	{
		m_pRobotDataTimer->cancel();
	}
}

void CPlayer::SyncToWs()
{
	::msg_maj::SyncRoleToWs proto;
	proto.set_uid(m_ulCharID);
	proto.set_room_id(m_unRoomID);
	proto.set_room_seat(m_usSeat);
	proto.set_room_card(m_nRoomCards);
	proto.set_robotplaying(m_bIsRobotPlaying);
	proto.set_disconnect(m_bDisconnect);
	proto.set_hiscongames(m_nHisConGames);
	proto.set_hismaxscore(m_nHisMaxScore);
	GameService::getMe().SendToWs(::comdef::msg_role,::msg_maj::sync_role_to_ws, m_unSessionID, 0,proto);
}

void CPlayer::AddEnterRoomOtherMsg(uint16_t usCmd, uint16_t usCCmd, const google::protobuf::Message& proData)
{
	BUFFER_CMD(PbMsgWebSS, send, MAX_USERDATASIZE);
	send->cmd = usCmd;
	send->cmdType = usCCmd;
	send->clientSessID = m_unSessionID;
	send->fepServerID = m_unFepServerID;
	send->size = proData.ByteSize();
	proData.SerializeToArray(send->data, send->size);
	m_vecEnterRoomOtherMsg.push_back(*send);

}

void CPlayer::SendEnterRoomOtherMsg()
{
	zSession* pFep = GameService::Instance()->SessionMgr()->getFep(m_unFepServerID);
	if (pFep == NULL)
	{
		ASSERT(0);
		return;
	}
	for (size_t i = 0; i < m_vecEnterRoomOtherMsg.size(); ++i)
	{
		PbMsgWebSS send = m_vecEnterRoomOtherMsg[i];
		pFep->sendMsg(&send, sizeof(PbMsgWebSS) + send.size);
	}
	m_vecEnterRoomOtherMsg.clear();
}


uint16_t CPlayer::GetHutimes() const
{
	uint16_t huCount = 0;
	for (std::vector<stScoreDetail>::const_iterator it = m_vecScoreDetail.begin(); it != m_vecScoreDetail.end(); ++it)
	{
		if (it->type == 1)
		{
			if (it->hu.huSeat == it->hu.mySeat && GetSeat() == it->hu.huSeat)
			{
				huCount++;
			}
		}
	}
	return huCount;
}

void CPlayer::GetHuTiles(std::vector<uint16_t>& vecHuTiles) const
{
	for (std::vector<stScoreDetail>::const_iterator it = m_vecScoreDetail.begin(); it != m_vecScoreDetail.end(); ++it)
	{
		if (it->type == 1)
		{
			if (it->hu.huSeat == it->hu.mySeat && GetSeat() == it->hu.huSeat)
			{
				vecHuTiles.push_back(it->hu.huTile);
			}
		}
	}
}

void CPlayer::GetHuTimesVec(std::vector<stHuDetail>& vecHuDetail)
{
	for (std::vector<stScoreDetail>::const_iterator it = m_vecScoreDetail.begin(); it != m_vecScoreDetail.end(); ++it)
	{
		if (it->type == 1)
		{
			if (it->hu.huSeat == it->hu.mySeat && GetSeat() == it->hu.huSeat)
			{
				vecHuDetail.push_back(it->hu);
			}
		}
	}
}

bool CPlayer::IsHued() const
{
	return GetHutimes() > 0;
}

void CPlayer::AddScore(const stHuDetail& hu)
{
	stScoreDetail stDetial;
	stDetial.type = 1;
	stDetial.hu = hu;
	m_vecScoreDetail.push_back(stDetial);
}

void CPlayer::AddScore(const stFengYuDetail& fengyu)
{
	stScoreDetail stDetial;
	stDetial.type = 2;
	stDetial.fengYu = fengyu;
	m_vecScoreDetail.push_back(stDetial);
}

void CPlayer::AddScore(const stHuaZhuDetail& huazhu)
{
	stScoreDetail stDetial;
	stDetial.type = 3;
	stDetial.huaZhu = huazhu;
	m_vecScoreDetail.push_back(stDetial);
}

void CPlayer::AddScore(const stDaJiaoDetail& dajiao)
{
	stScoreDetail stDetial;
	stDetial.type = 4;
	stDetial.daJiao = dajiao;
	m_vecScoreDetail.push_back(stDetial);
}

void CPlayer::AddScoreBackTax(int16_t backTax)
{
	stScoreDetail stDetial;
	stDetial.type = 5;
	stDetial.backTax = backTax;
	m_vecScoreDetail.push_back(stDetial);
}

void CPlayer::AddScoreHujzy(int16_t hujzy)
{
	stScoreDetail stDetial;
	stDetial.type = 6;
	stDetial.huJzy = hujzy;
	m_vecScoreDetail.push_back(stDetial);
}

int16_t CPlayer::GetLastGangScore()
{
	uint16_t score = 0;
	for (std::vector<stScoreDetail>::reverse_iterator it = m_vecScoreDetail.rbegin(); it != m_vecScoreDetail.rend(); ++it)
	{
		if (it->type == 2)
		{
			if (it->fengYu.huSeat == it->fengYu.mySeat && GetSeat() == it->fengYu.huSeat)
			{
				score = it->fengYu.score;
				break;
			}
		}
	}
	return score;
}

void CPlayer::AddGuoPengPai(int16_t usPai)
{
	std::set<uint16_t>::iterator it = m_setGuoPengPai.find(usPai);
	if (it == m_setGuoPengPai.end())
	{
		m_setGuoPengPai.insert(usPai);
	}
}

void CPlayer::AddGuoGangPai(int16_t usPai)
{
	std::set<uint16_t>::iterator it = m_setGuoGangPai.find(usPai);
	if (it == m_setGuoGangPai.end())
	{
		m_setGuoGangPai.insert(usPai);
	}
}

bool CPlayer::HasGuoGangPai(int16_t usPai)
{
	std::set<uint16_t>::iterator it = m_setGuoGangPai.find(usPai);
	if (it != m_setGuoGangPai.end())
	{
		return true;
	}
	return false;
}


