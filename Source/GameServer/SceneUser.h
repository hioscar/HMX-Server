#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#include "SrvEngine.h"
#include "SceneEntryPk.h"
#include "base/hmx_data.pb.h"

/*
 *	Detail: ��ɫ��  
 *  Created by hzd 2014-12-17
 */
class SceneUser : public SceneEntryPk
{
public:
	SceneUser(const ::data::UserInfo& proto);
	~SceneUser();

	inline uint64_t GetUID() const { return dataProto.id(); }
	inline uint64_t GetSessionID() const { return nSessionID; }
	inline uint64_t GetFepSessID() const { return nFepSessionID; }

private:

	int64_t nSessionID;			/* payersessid*/
	int32_t nFepSessionID;		/* Fep�Ự */
	bool initDataFinish;		/* �Ƿ�װ�������� */
	bool clientReady;			/* ǰ��״̬ 0 ok,1 ������Դ�� */ 
	bool userModity;			/* �Ƿ����ݱ䶯(0��,1��) */

	//S::t_UserSceneBase userbase;		/* ��ɫ�������� */

	::data::UserInfo dataProto;

public:

	bool move(Cmd::stUserMoveMoveUserCmd *rev);
	void online(); 
	
	// �ɳ�������,���Ը��ݲ�ͬ�ĳ���,���Ƶ��õ�Ƶ��
	// ͨ��Ҫ��200ms���ڵ���һ��
	void Timer(const zTaskTimer* t);

public:

	/* ���볡����Ҫ�������� */ 
	void sendMainToMe();

	// ���¼���PK����
	void setupCharBase(); 

	void sendCmdToMe(NetMsgSS* pMsg, int32_t nSize);
	void sendToFep(NetMsgSS* pMsg, int32_t nSize);
	void sendToDp(NetMsgSS* pMsg, int32_t nSize);
	void sendToWs(NetMsgSS* pMsg, int32_t nSize);

public:

	bool CheckMoneyEnough(int32_t type,int32_t num);
	bool TrySubMoney(int32_t type, int32_t num);
	bool SubMoney(int32_t type, int32_t num, bool notify = true, bool isTry = false);
	
public:

	/**
	* \brief �ı��ɫ��hp
	* \param hp �����HP
	*/
	virtual void changeHP(const SDWORD &hp);

	/**
	* \brief �ı��ɫ��sp
	* \param sp �����SP
	*/
	virtual void changeSP(const SDWORD &sp);

	/**
	* \brief �ı��ɫ��mp
	* \param mp �����MP
	*/
	virtual void changeMP(const SDWORD &mp);

	/**
	* \brief �ж��Ƿ��ǵ���
	* \return true �� false ����
	*/
	virtual int isEnemy(SceneEntryPk *entry, bool notify = false, bool good = false);

	/**
	* \brief ��ȡ�Լ�������,һ�����NPC����,Player���������Լ�
	* \return NULL�������˵Ķ���ָ��
	*/
	virtual SceneEntryPk *getMaster();

	/**
	* \brief �õ����ϲ������
	*
	* \return ����
	*/
	virtual SceneEntryPk *getTopMaster();

	/**
	* \brief �жϽ�ɫ�Ƿ�����
	*/
	virtual bool isDie();

	/**
	* \brief ��ȡ��ɫ�ļ���
	*/
	virtual DWORD getLevel() const;

	int32_t getVip() const
	{
		return 0;
	}

	int32_t getCountry() const
	{
		return 0;
	}

	/**
	* \brief ��ȡ���е���
	* \return ���ظ����͵����е���
	*/
	virtual DWORD getFiveType() { return 0; }

	/**
	* \brief ��Ҫ��ְҵ����,��������ʹ�õļ�������
	*/
	virtual bool needType(const DWORD &needtype);

	/**
	* \brief �Ƿ��иü�����Ҫ������
	* \return true �� false û��
	*/
	virtual bool needWeapon(DWORD skillid);

	/**
	* \brief �Ƿ�Pk����
	* \param other PK�����
	* \return true �� false ��
	*/
	virtual bool isPkZone(SceneEntryPk *other = NULL);

	/**
	* \brief ������Ʒ�����ͷ���
	* \param object ������Ʒ������
	* \param num ������Ʒ������
	* \return true ���ĳɹ� false ʧ��
	*/
	virtual bool reduce(const DWORD &object, const BYTE num);

	/**
	* \brief ����������Ʒ�Ƿ��㹻
	* \param object ������Ʒ������
	* \param num ������Ʒ������
	* \return true �㹻 false ����
	*/
	virtual bool checkReduce(const DWORD &object, const BYTE num);
	/**
	* \brief ��ȡװ���˺��ӳ�
	* \return �˺��ӳ�
	*/
	virtual WORD getDamageBonus() { return 0; }

	virtual void showCurrentEffect(const WORD &state, bool isShow, bool notify = true);

	virtual bool preAttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics = true, const bool good = false);

	/**
	* \brief �ý�ɫ����
	* \param dwTempID �����ߵ���ʱID
	*/
	virtual void toDie(const DWORD &dwTempID);

	virtual SWORD directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify = false);



};

#endif



