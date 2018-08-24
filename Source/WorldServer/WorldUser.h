#ifndef __WORLD_USER_H_
#define __WORLD_USER_H_

#include "SrvEngine.h"
#include "base/hmx_data.pb.h"

/*
  ��̬���������û���
  id=uid,tempid=sessid,name=nick
 */
class WorldUser : public zEntry
{
public:
	WorldUser(const ::msg_maj::RoleWs& proto);
	~WorldUser();
	inline uint64_t GetID(){ return m_dataProto.id(); }
	inline uint64_t GetTempID(){ return m_usClientSessID; }
	inline const std::string& GetName(){ return m_dataProto.nickname(); }
	inline const std::string& GetAccID() { return m_dataProto.account(); }
	inline void SetClientSessID(uint64_t _clientSessID) { m_usClientSessID = _clientSessID; }
	inline uint64_t GetClientSessID() const { return m_usClientSessID; }

	void sendMsgToFep(uint16_t cmd, uint16_t cmdType, const ::google::protobuf::Message& proto);
	void sendMsgToSs(uint16_t cmd, uint16_t cmdType, const ::google::protobuf::Message& proto);

	inline zSession* GetFepSession() { return m_fepSession; }
	inline void SetFepSession(zSession* _fepSession) { m_fepSession = _fepSession; }

	inline zSession* GetSceneSession() { return m_sceneSession; }
	inline void SetSceneSession(zSession* _sceneSession) { m_sceneSession = _sceneSession; }

	inline const std::vector<int32_t>& GetProxyServerList() const { return m_proxyServerList; }
	void refreshProxyServerList(const std::vector<int32_t>& serid_list);

	inline uint64_t GetRoomID() const { return m_usRoomID; }

	// player����Ĳ���������ͨ���ýӿ�ȥ����
	void UpdateRoleFromSs(const ::msg_maj::SyncRoleToWs& proto);

private:
	
	uint64_t&				m_usClientSessID;
	zSession*				m_fepSession;
	zSession*				m_sceneSession;
	::msg_maj::RoleWs		m_dataProto;

	std::vector<int32_t>	m_proxyServerList;		// ���Խ���Ĵ�����

	uint64_t				m_usRoomID;				// ��ǰ�Ƿ��ڷ�����
	uint32_t				m_usRoomSeat;			// �Լ��ڷ����״̬
	bool					m_bDisconnect;
	bool					m_bRobotPlaying;
	uint32_t				m_usHisConGames;
	uint32_t				m_usHisMaxScore;	

};


#endif

