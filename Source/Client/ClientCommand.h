#ifndef __GAMECOMMAND_H_
#define __GAMECOMMAND_H_

#define MAX_PATH1 260

#include "NetSocket.h"
#include "SrvEngine.h"
#include "Single.h"

class Player;
class GameCommand;

typedef void(GameCommand::*CommandFun)(const char* secondArgs);

struct KeyCommand
{
	KeyCommand( const char* id , const char* doc , CommandFun call )
	{
		this->id = id;
		this->doc = doc;
		this->callBack = call;
	}

	std::string	id;
	std::string	doc;
	CommandFun	callBack;
};

typedef vector< KeyCommand > VectorCommand;
typedef vector< KeyCommand >::iterator VectorCommandIter;


/*
 *  �������������� 
 */
class GameCommand : public Single<GameCommand>
{
protected:
	friend class Single<GameCommand>;
	GameCommand();
	~GameCommand();

public:
    
    void Init();
	void LoopInput();
	void ShowCmd();

private:

	bool ParseCommand(const char* command);
	void PrintSearch(const char* command);

	// ͨ�÷�������(���Ҳ�����������ʱ������ø�������в��ҿ��ܵĽ��)
	void AnalysisCmd(const char* command);

	// ִ������ 
	void CommandHelp(const char* command);

	// ��¼�ʺ�hzd
	void LoginAccount(const char* command);

	// ��¼�ʺ�kfc
	void LoginAccount2(const char* command);

	// ѡ���ɫ
	void RoleSelect(const char* command);

	// ������ɫ
	void RoleCreate(const char* command);

	// ɾ����ɫ
	void RoleDelete(const char* command);

	// ���س���
	void SceneLoad(const char* command);

	// ���볡��
	void SceneIn(const char* command);

	// ��������
	void ChatToWorld(const char* command);

	// �ƶ�λ�� 
	void MovePosition(const char* command);

	void RelList(const char* command);
	void RelAdd(const char* command);
	void RelRemove(const char* command);

private:

	VectorCommand	commands;
	char			mArrBuffer[ MAX_PATH1 ];
	int32_t			mCommandCount;
};



#endif


