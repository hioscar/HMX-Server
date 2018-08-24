#include "GatewaysServer.h"
#include "GameService.h"
#include "GateUser.h"
#include "PlayerMsgHandler.h"

extern DWORD cancel_country_need_money;
extern DWORD is_cancel_country;


template<typename TMsg>
struct MsgSendToAllPlayer : public execEntry<zSession>
{
	MsgSendToAllPlayer(TMsg* __msg, int32_t __size) :_msg(__msg), _size(__size)
	{
	}
	virtual bool exec(zSession *entry)
	{
		if (entry->GetRemoteServerType() == 0)
		{
			PlayerMsgHandler::getMe().SendToPlayer(entry, _msg, _size);
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
* \param pUser: ������Ƶ�����û�
*/
GateChannel::GateChannel(GateUser *pUser) :zEntry()
{
	creater->_entry_id = pUser->GetID();
	creater->_entry_tempid = pUser->GetTempID();
	creater->_entry_name = pUser->GetName();
}

GateChannel::GateChannel(DWORD chID, const std::string& _name)
{
	creater->_entry_id = chID;
	creater->_entry_tempid = chID;
	creater->_entry_name = _name;
}

GateChannel::~GateChannel()
{

}

/**
* \brief ���͸���Ƶ���������û�
*
*
* \param cmd: ��������
* \param len:���ݳ���
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendCmdToAll(const NetMsgSS *cmd, int len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);

	//MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);

	return true;
}

/**
* \brief �뿪Ƶ��
*
*
* \param uname: �뿪��Ƶ�����û�
* \return ��Ƶ���Ƿ��ܼ�������
*/
bool GateChannel::remove(const char *uname)
{
	WORD found = has(uname);
	if (found != (WORD)-1)
	{
		/*H::logger->info("%s�뿪%s������Ƶ��", uname, creater->GetName().c_str());
		C::RtChannelLeave send;
		send.channelID = _entry_tempid;
		strncpy(send.name, uname, MAX_NAMESIZE);
		sendCmdToAll(&send, sizeof(send));

		if ((found + 1) < (WORD)userlist.size())
		{
			userlist[found] = userlist.back();
		}
		userlist.pop_back();*/
	}
	if (userlist.empty())
		return false;
	else
		return true;
}

/**
* \brief ��������Ƶ��
*
*
* \param pUser: Ҫ������û�
* \return �����Ƿ�ɹ�
*/
bool GateChannel::add(GateUser *pUser)
{
	if (pUser != NULL)
	{
		WORD found = has(pUser->GetName().c_str());
		if (found == (WORD)-1)
		{
			H::logger->info("%s����%s������Ƶ��", pUser->GetName().c_str(), creater->GetName().c_str());

			//GateUser temp;
			//temp._entry_id = pUser->GetID();
			//temp._entry_tempid = pUser->GetTempID();
			//temp._entry_name = pUser->GetName();
			//userlist.push_back(temp);

			/* ���Լ����͸������� */
			//C::RtChannelJion send;
			//send.channelID = _entry_tempid;
			//strncpy(send.name, pUser->GetName().c_str(), MAX_NAMESIZE);
			//sendCmdToAll(&send, sizeof(send));

			/* �������г�Ա���Լ� */
			//for (DWORD i = 0; i < userlist.size(); i++)
			//{
			//	strncpy(send.name, userlist[i].name, MAX_NAMESIZE);
			//	pUser->send(&send, sizeof(send));
			//}
			return true;
		}
	}
	return false;
}

/**
* \brief ����Ƶ�����Ƿ����ĳ��
*
*
* \param name: �û���
* \return ���ڷ��ظ��û���Ƶ���е�λ��,�����ڷ���-1
*/
WORD GateChannel::has(const char *name)
{
	if (name)
	{
		for (DWORD i = 0; i < userlist.size(); i++)
		{
			if (strncmp(userlist[i].GetName().c_str(), name, MAX_NAMESIZE) == 0)
				return i;
		}
	}
	return (WORD)-1;
}

/**
* \brief ת��������Ϣ��9��
*
*
* \param pUser: ��������
* \param rev: ת��������
* \param cmdLen: ���ݳ���
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendNine(GateUser *pUser, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
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
* \brief ���͹��ҹ���
*
*
* \param countryID: countryID
* \param infoType: infoType
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendCountryInfo(DWORD countryID, DWORD infoType, const char *pattern, ...)
{

	return true;
}

/**
* \brief ����ȫ������
*
* \param infoType: infoType
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendAllInfo(DWORD infoType, const char *pattern, ...)
{

	return true;
}

/**
* \brief ������Ϣ������Ƶ��
*
*
* \param pUser: ��������
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendCountry(GateUser *pUser, const char *pattern, ...)
{

	return true;
}

/**
* \brief ��������Ϣ������Ƶ��
*
*
* \param pUser: ����ָ����û�
* \param rev: �յ���ָ��
* \param cmdLen: ָ���
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendCountry(GateUser *pUser, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = 0;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
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
bool GateChannel::sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = mapID;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

/**
* \brief ת��������Ϣ
*
*
* \param teamid: ����id
* \param rev: ��Ҫת����ָ��
* \param cmdLen: ָ���
* \return ת���Ƿ�ɹ�
*/
bool GateChannel::sendTeam(DWORD teamid, const NetMsgSS *cmd, DWORD len)
{
	//BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	//send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	//send->regid = teamid;
	//send->size = len;
	//memcpy(send->data, cmd, len);
	//MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	//GameService::getMe().SessionMgr()->execEveryConn(exec);
	return true;
}

/**
* \brief ����ϵͳ��Ϣ
*
*
* \param pUser: Ҫ������Ϣ���û�
* \param type: ϵͳ��Ϣ����
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendSys(GateUser *pUser, int type, const char *pattern, ...)
{

	return false;
}

bool GateChannel::sendSys(DWORD dwUserTempID, int type, const char *pattern, ...)
{
	//GateUser *pToUser = GateUserManager::getMe().getUserByTempID(dwUserTempID);
	//if (pToUser)
	//{
	//	char buf[MAX_CHATINFO];
	//	getMessage(buf, MAX_CHATINFO, pattern);
	//	zRTime ctv;
	//	Cmd::stChannelChatUserCmd send;
	//	send.dwType = Cmd::CHAT_TYPE_SYSTEM;
	//	send.dwSysInfoType = type;//ϵͳ��Ϣ������
	//	send.dwChatTime = ctv.sec();
	//	bzero(send.pstrName, sizeof(send.pstrName));
	//	bzero(send.pstrChat, sizeof(send.pstrChat));
	//	strncpy((char *)send.pstrChat, buf, MAX_CHATINFO - 1);
	//	pToUser->sendCmdToMe(&send, sizeof(send));
	//	return true;
	//}
	return false;
}

/**
* \brief ˽��
*
*
* \param pUser: ��������
* \param rev:����ָ��
* \param cmdLen: ָ���
* \return �����Ƿ�ɹ�
*/
bool GateChannel::sendPrivate(GateUser *pUser, const NetMsgSS *rev, DWORD cmdLen)
{

	return true;
}

/**
* \brief Ψһʵ��
*
*/
GateChannelM::GateChannelM()
{
	channelUniqeID = new zUniqueDWORDID(1);
}

GateChannelM::~GateChannelM()
{
	S_SAFE_DELETE(channelUniqeID);
}

/**
* \brief �õ�һ��Ψһ���
*
*
* \param tempid: Ψһ���(���)
* \return �õ��ı���Ƿ�Ψһ
*/
bool GateChannelM::getUniqeID(QWORD &tempid)
{
	tempid = channelUniqeID->get();
	return (tempid != channelUniqeID->invalid());
}

/**
* \brief �ջ�һ��Ψһ���
*
*
* \param tempid: �ջصı��
*/
void GateChannelM::putUniqeID(const QWORD &tempid)
{
	channelUniqeID->put(tempid);
}

/**
* \brief ��������Ƶ��
*
*
* \param channel: Ƶ��
* \return �����Ƿ�ɹ�
*/
bool GateChannelM::add(GateChannel *channel)
{
	bool ret;
	mlock.lock();
	ret = addEntry(channel);
	mlock.unlock();
	return ret;
}

/**
* \brief ������Ƶ����ɾ��һ���û�
*
*
* \param name: �û���
*/
void GateChannelM::removeUser(const char *name)
{
	// ��������Ƶ�����name�û�
	for (zEntryName::hashmap::iterator it = zEntryName::ets.begin(); it != zEntryName::ets.end(); it++)
	{
		GateChannel *temp = (GateChannel *)it->second;
		temp->remove(name);
	}
}

/**
* \brief ������Ƶ����ɾ��һ������Ƶ��
*
*
* \param dwChannelID: Ƶ��id
*/
void GateChannelM::remove(DWORD dwChannelID)
{
	GateChannel *ret = NULL;
	mlock.lock();
	ret = (GateChannel *)zEntryID<1>::getEntryByID(dwChannelID);
	removeEntry(ret);
	mlock.unlock();
}

/**
* \brief �õ�һ������Ƶ��
*
*
* \param dwChannelID: Ƶ��id
* \return ����Ƶ��
*/
GateChannel *GateChannelM::get(DWORD dwChannelID)
{
	GateChannel *ret = NULL;
	mlock.lock();
	ret = (GateChannel *)zEntryID<1>::getEntryByID(dwChannelID);
	mlock.unlock();
	return ret;
}

GateChannel* GateChannelM::CreateObj(GateUser *pUser)
{
	return objpool.CreateObj(pUser);
}

GateChannel* GateChannelM::CreateObj(DWORD chID, const std::string& _name)
{
	return objpool.CreateObj(chID, _name);
}

void GateChannelM::DestroyObj(GateChannel* obj)
{
	objpool.DestroyObj(obj);
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



