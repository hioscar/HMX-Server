#ifndef _CROOM_MGR_H_
#define _CROOM_MGR_H_
#include "Global.hpp"
#include "FogsTimerService.hpp"

class CRoom;

static const uint32_t g_unRoomIDNum = 100000;

class CRoomMgr : public Singleton<CRoomMgr>
{
public:
	CRoomMgr();
	~CRoomMgr();

	bool Init();

	void Release();

	uint32_t GenerateRoomID();

	void RecoveryRoomID(uint32_t unRoomID);

	//����1:�������� 2:��Ϸ���� 3:���� 4:������ز�������
	CRoom* CreateRoom(::msg_maj::RoomType roomType, msg_maj::maj_type majType, uint64_t roomerID, uint64_t matchID, const ::msg_maj::RoomOption& option);

	void DelRoomByID(uint32_t unRoomID);

	CRoom* GetRoomByID(uint32_t unRoomID) const;

	void AddCloseRoom(uint32_t unRoomID);

	void ClearRoom();

private:

	typedef std::map<uint32_t, CRoom*> mapRoom;
	mapRoom m_mapRoom;

	std::set<uint32_t> m_setCloseRoom;

	fogs::FogsTimer* m_pTimer;

	uint32_t m_arrRoomID[g_unRoomIDNum];	//������б�

	uint32_t m_unRemainRoomIDNum;	//ʣ�෿�������

	uint32_t m_unRoomIDMin;			//��С�����

	uint32_t m_unRoomIDMax;			//��󷿼��
};

#endif // !_CROOM_MGR_H_
