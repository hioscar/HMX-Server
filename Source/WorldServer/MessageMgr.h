#ifndef __MESSAGE_MGR_H_
#define __MESSAGE_MGR_H_

#include "SrvEngine.h"
#include "base/hmx_data.pb.h"

#define MAX_MSG_LENGTH 300

typedef std::map<int32_t,std::string, std::greater<int32_t> > ChatMsgMapType;
typedef std::map<int32_t, std::string, std::greater<int32_t> > TeamChatMsgMapType;

/*
 *	������ʱ���书�ܣ������ӵ�ַ������Ϳ��Բ鿴��ͬʱ�����Խ��й���
 *  �鿴��һ���������Զ���������
 *
 */
class zMessage : public zEntry
{
public:
	zMessage();
	inline uint64_t GetID(){ return id; }
	inline uint64_t GetTempID(){ return _entry_tempid; }
	inline const std::string& GetName(){ return _entry_name; }

private:

	int64_t id;
	int32_t createTime;
	int64_t sendUid;
	char sendName[MAX_NAMESIZE + 1];
	int32_t sendTime;
	char msg[MAX_MSG_LENGTH + 1];


};


class MessageMgr : protected zEntryMgr< zEntryID<0> >
{
public:
	MessageMgr();
	~MessageMgr();

	void loadDB();


	void doUserCmd(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	zMessage* CreateObj();
	void DestroyObj(zMessage* obj);

	bool addMessage(zMessage* mess);
	void removeMessage(zMessage* mess);
	void removeMessageAll();
	void removeMessageBefore(int32_t time);

	zMessage* getMessage(QWORD id);
	void getMessageNearest(int num);
	void getMessageNearestFrom(int num,QWORD fromID);
	void getMessageFromTo(QWORD formID,QWORD toID);

private:

	zObjPool<zMessage> objpool;


private:

	/* ������Ϣ �Է�ID=>��ϢID=>��Ϣ���� */
	std::map<int64_t, ChatMsgMapType > chatOneMsg;

	/* Ⱥ����Ϣ��ȺID=>��ϢID=>��Ϣ���� */
	/* ������Ϣ��ͨ��ָ����ϢIDȥ������ݣ�����δ�����ģ����ᵥ������һ�ݣ�����ǹۿ�������ᱣ�� */
	/* ��������ֻ����WS�� */
	std::map<int32_t, TeamChatMsgMapType > chatTeamMsg;

};

#endif


