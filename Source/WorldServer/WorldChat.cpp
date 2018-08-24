#include "WorldServer.h"
#include "WorldUser.h"
#include "GameService.h"

extern DWORD cancel_country_need_money;
extern DWORD is_cancel_country;


template<typename TMsg>
struct MsgSendToAllFep : public execEntry<zSession>
{
	MsgSendToAllFep(TMsg* __msg, int32_t __size) :_msg(__msg), _size(__size)
	{
	}
	virtual bool exec(zSession *entry)
	{
		if (entry->GetRemoteServerType() == 1)
		{
			entry->sendMsg(_msg, _size);
		}
		return true;
	}
	TMsg* _msg;
	int32_t _size;
};


/*
* \brief ���û�������Ϣ
* ����û����ڸ÷�����,����sessionת��
*
* \param id �û���ID
* \param cmd ��Ϣ
* \param len ��Ϣ����
*
* \return �Ƿ�ɹ�
*/
bool sendCmdByID(DWORD id, const void *cmd, int len)
{

	return true;
}


/*
* \brief ���û�������Ϣ
* ����û����ڸ÷�����,����sessionת��
*
* \param id �û�����ʱID
* \param cmd ��Ϣ
* \param len ��Ϣ����
*
* \return �Ƿ�ɹ�
*/
bool sendCmdByTempID(DWORD id, const void *cmd, int len)
{

	return true;
}


/*
* \brief ���û�������Ϣ
* ����û����ڸ÷�����,����sessionת��
*
* \param name �û�������
* \param cmd ��Ϣ
* \param len ��Ϣ����
*
* \return �Ƿ�ɹ�
*/
bool sendCmdByName(char * name, const void *cmd, int len)
{

	return true;
}

/**
* \brief ���캯��
*
*
* \param user: ������Ƶ�����û�
*/
WorldChannel::WorldChannel() :zEntry()
{
}

WorldChannel::~WorldChannel()
{

}

//const dbCol chat_fields[] =
//{
//	{ "ID",DB_QWORD,sizeof(int64_t) },
//	{ "NAME",DB_STR,MAX_NAMESIZE + 1 },
//	{ "INFO",DB_BIN2,0 },
//	{ NULL,0,0 }
//};

#pragma pack(push,1)
struct stChatmsgRecord
{
	int64_t id;
	char name[MAX_NAMESIZE + 1];
	int32_t size;
	char data[0];
};
#pragma pack(pop)


bool WorldChannel::loadDB()
{
	//BUFFER_CMD(stChatmsgRecord, data, MAX_USERDATASIZE);

	//char wheres[100];
	//memset(wheres, 0, sizeof(wheres));
	//sprintf(wheres, "`id`=%lld", this->id);
	//
	//int ret = GameService::getMe().getDbMysql()->ExecSelectLimit("Chatmsg", chat_fields, wheres, NULL, (unsigned char*)data);
	//if (ret == 1)
	//{
	//	strncpy(this->name, data->name, MAX_NAMESIZE);
	//	// ��������������
	//	::protobuf::ChatMsgBinary proto;
	//	proto.ParseFromArray(data->data, data->size);
	//	unserialize(proto);
	//	return true;
	//}
	//else
	//{
	//	H::logger->error("����Ƶ���ڴ�ʧ�ܣ��Ҳ�������");
	//	return false;
	//}
	return true;
}

void WorldChannel::saveDB()
{
	/*BUFFER_CMD(stChatmsgRecord, data, MAX_USERDATASIZE);

	data->id = this->id;
	strncpy(data->name, this->name, MAX_NAMESIZE);

	::protobuf::ChatMsgBinary proto;
	serialize(proto);
	data->size = proto.ByteSize();
	proto.SerializeToArray(data->data, MAX_USERDATASIZE);

	static char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%llu", this->id);

	int ret = GameService::getMe().getDbMysql()->ExecUpdate("Chatmsg", chat_fields, (const char*)data, wheres);
	if (ret == 0)
	{
		H::logger->info("����Ƶ���ɹ�!");
	}
	else
	{
		H::logger->error("����Ƶ��ʧ��!");
	}*/
}

/**
* \brief ���͸���Ƶ���������û�
*
*
* \param cmd: ��������
* \param len:���ݳ���
* \return �����Ƿ�ɹ�
*/
bool WorldChannel::sendCmdToAll(const NetMsgSS *cmd, int len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);

	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);

	return true;
}

/**
* \brief ת��������Ϣ��9��
*
*
* \param user: ��������
* \param rev: ת��������
* \param cmdLen: ���ݳ���
* \return �����Ƿ�ɹ�
*/
bool WorldChannel::sendNine(WorldChannel::UserData *user, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

#define getMessage(msg,msglen,pat)  \
	do  \
{  \
	va_list ap;  \
	bzero(msg,msglen);  \
	va_start(ap,pat);    \
	vsnprintf(msg,msglen - 1,pat,ap);  \
	va_end(ap);  \
}while(false)


/**
* \brief ��������Ϣ������Ƶ��
*
*
* \param user: ����ָ����û�
* \param rev: �յ���ָ��
* \param cmdLen: ָ���
* \return �����Ƿ�ɹ�
*/
bool WorldChannel::sendCountry(WorldChannel::UserData *user, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}


/**
* \brief ���͸��õ�ͼ�������û�
*
* \param mapID ��ͼID
* \param cmd ��Ϣ
* \param len: ����
* \return �����Ƿ�ɹ�
*/
bool WorldChannel::sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = mapID;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

/**
* \brief ˽��
*
*
* \param user: ��������
* \param rev:����ָ��
* \param cmdLen: ָ���
* \return �����Ƿ�ɹ�
*/
bool WorldChannel::sendPrivate(WorldChannel::UserData *user, const NetMsgSS *rev, DWORD cmdLen)
{

	return true;
}

bool WorldChannel::sendTeam(QWORD teamid, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = teamid;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllFep<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

/**
* \brief Ψһʵ��
*
*/
WorldChannelM::WorldChannelM()
{

	maxid = 0;
}

WorldChannelM::~WorldChannelM()
{
	
}

void WorldChannelM::loadDB()
{
//	const dbCol msg_id[] =
//	{
//		{ "ID",DB_QWORD,sizeof(QWORD) },
//		{ NULL,0,0 },
//	};
//
//#pragma pack(push,1)
//	struct dbUserID
//	{
//		QWORD id;
//	};
//#pragma pack(pop)
//
//	dbUserID* dataList, *dataTmp;
//	int ret = GameService::getMe().getDbMysql()->ExecSelect("Chatmsg", msg_id, NULL, NULL, (unsigned char**)&dataList);
//	if (ret > 0)
//	{
//		int loadcount = 0;
//		int failcount = 0;
//		for (int c = 0; c < ret; ++c)
//		{
//			dataTmp = &dataList[c];
//			WorldChannel* channel = CreateObj();
//			channel->id = dataTmp->id;
//			if (channel->loadDB() && add(channel))
//			{
//				loadcount++;
//			}
//			else
//			{
//				failcount++;
//				H::logger->error("����Ƶ��ʧ��[ID:%lld]", channel->id);
//				remove(channel);
//			}
//		}
//
//		S_SAFE_DELETE_VEC(dataList);
//		H::logger->info("��%d�����ݣ��ɹ�����%d��,ʧ��%d��", ret, loadcount, failcount);
//
//	}
}

/**
* \brief ��������Ƶ��
*
*
* \param channel: Ƶ��
* \return �����Ƿ�ɹ�
*/
bool WorldChannelM::add(WorldChannel *channel)
{
	return zEntryMgr< zEntryID<0>, zEntryID<1>, zEntryName >::addEntry(channel);
}

/**
* \brief ������Ƶ����ɾ��һ������Ƶ��
*
*
* \param dwChannelID: Ƶ��id
*/
void WorldChannelM::remove(WorldChannel* channel)
{
	zEntryMgr< zEntryID<0>, zEntryID<1>, zEntryName  >::removeEntry(channel);
}

/**
* \brief �õ�һ������Ƶ��
*
*
* \param dwChannelID: Ƶ��id
* \return ����Ƶ��
*/
WorldChannel *WorldChannelM::get(QWORD dwChannelID)
{
	return (WorldChannel *)zEntryID<0>::getEntryByID(dwChannelID);
}

/**
* \brief ��16������תΪ10����
*
*
* \param ch: 16�����ַ�
* \return ת�����10������
*/
BYTE hexchtoi(char &ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return BYTE(ch - '0');
	}
	else if ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
	{
		return BYTE(toupper(ch) - 'A') + 10;
	}
	return 0;
}



