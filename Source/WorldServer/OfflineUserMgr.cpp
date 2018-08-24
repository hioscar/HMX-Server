#include "OfflineUserMgr.h"
#include "SceneRegMgr.h"
#include "GameService.h"

#include "MysqlProtobufHelper.h"

OfflineUserMgr::OfflineUserMgr()
{

}

OfflineUserMgr::~OfflineUserMgr()
{

}

void OfflineUserMgr::loadDB()
{
	::fogs::proto::msg::QueryOfflineUserProto proto;
	int32_t nRet = doQueryRepeatedProto(*GameService::Instance()->GetDataRef(), "SELECT * FROM `tb_role`", *proto.mutable_user_list());
	if (nRet != 0)
	{
		H::logger->error("���� USER ����!");
		return;
	}

	int usercount = 0;
	int failcount = 0;
	for (int i = 0; i < proto.user_list_size(); ++i)
	{
		if (NULL == addUser(proto.user_list(i)))
		{
			failcount++;
		}
		else
		{
			usercount++;
		}
	}

	H::logger->info("��%d�����ݣ��ɹ�����%d��,ʧ��%d��", usercount + failcount, usercount, failcount);
}

OfflineUser* OfflineUserMgr::addUser(const ::msg_maj::RoleOff& proto)
{
	OfflineUser* obj = objpool.construct(proto);
	bool ret = zEntryMgr<  zEntryID<0>, zEntryName >::addEntry(obj);
	if (!ret)
	{
		objpool.destroy(obj);
		return NULL;
	}
	return obj;
}