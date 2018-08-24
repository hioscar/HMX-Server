#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <bitset>
#include <assert.h>

#include "SrvEngine.h"
#include "UnorderedSet.h"


class SceneRegion;
class Scene;

/*------------------------------------------------------------------
 *
 * @Brief : ʵ�常�ָ࣬�ڵ�ͼ�Ͽɴ��ڵ�ʵ�壬��NPC��Buff,��ң������
 *			���Ƕ�����ʵ�ʵ�λ�ã�ͬʱҲ���ڳ����г��֣�������Ҫ�̳г���
 *			Ƶ��ע��ӿڣ���Ҫʵ��λ��Ƶ���ӿ�
 * @Author: hzd 
 * @File  : Entity.h
 * @Date  : 2015/09/19 00:16
 * @Copyright (c) 2015,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
class SceneEntryPk : public zSceneEntry 
{
public:
	SceneEntryPk(const SceneEntryType entrytype);
	virtual ~SceneEntryPk() {}

	virtual int32_t getLevel() { return 0;}
	virtual int32_t getHp(){ return 0;}
	virtual int32_t getHpMax(){ return 0;}
	virtual int32_t getMp(){return 0;}
	virtual int32_t getMpMax(){return 0;}

	inline const zPos &getPos() const { return pos; }
	void setPos(const zPos& zPos) { pos = zPos; }

public:

	Scene*	scene; 

	///����ս��״̬��ʱ�� 
//	zRTime endBattleTime;
	///ʩ���� 
	DWORD curMagicManID;
	///��ʩ��������  
	DWORD curMagicManType;
	///���� 
	DWORD curTargetID;
	///�������� 
	DWORD curTargetType;

	bool attackAction;  /// �������
	bool moveAction;  /// �ƶ����
	bool skillAction;   /// ���ܹ������
	bool ignoreDam;    /// �����˺�
	bool ignorePhysicDam; /// ���������˺�
	bool ignoreMagicDam; /// ����ħ���˺�
	bool notifyHMS;    /// ֪ͨHP,MP,SP�ı�
	bool maxattack;    /// ����ȡ����
	bool mdeftozero;   /// ħ���������0
	bool pdeftozero;   /// ħ���������0
	bool useRes;    /// �ɷ�ʹ����Ʒ
	bool isAutoRestitute; // �Ƿ��Զ��ָ�
	bool frenzy;       /// ��״̬
	bool huntermark;  /// ���ֱ��
	bool isPhysics;    /// ���㹫ʽ������   
	bool dropweapon;   /// ��е
	bool tosh;        /// ��������
	bool stone;      /// ʯ��
	bool watchTrap;    /// �۲�����
	bool mhpd;  /// ħ���˺�����,�����˺��ӱ���־��
	bool blazeflag; ///����ϵ�����ӳɱ�־
	bool levinflag;  ///�׵�ϵ�����ӳɱ�־
	bool trapflag;  ///����ϵ�����ӳɱ�־
	bool iceflag;  ///��ϵ�����ӳɱ�־
	DWORD swapdamcharid; ///����ʩ���ߵ���ʱID
	DWORD swapdamcharid2; ///�ذ�ʩ���ߵ���ʱID
	bool changeface;  ///������,���Է��ʹ���NPC
	bool hideme;     /// �����Լ�
	bool icebox;   /// �����״̬
	bool liquidState; ///Һ̬�����赲��
	BYTE resist;     ///��,��һ�ε����˺��Ļ���
	BYTE dmpbyhp;  ///��ħ����
	BYTE mdmtomp;  ///�������˺�ת��ħ��ֵ�ٷֱ�
	BYTE mdmtompper; ///�������˺�ת��ħ��ֵ�ٷֱȼ���
	SDWORD icedam;  ///����������յ��˺���ֵ
	QWORD unitaryBattleKeepTime; //һԪ�󷨳���ʱ��
	SDWORD dietodam; ///����������ֵ
	bool attacklow; ///������ȡ����
	BYTE killnow; //һ����ɱ
	BYTE diewithme; //ѪծѪ��
	BYTE switchdie; //ͬ��ת������״̬�ļ���
	BYTE summonsplit; //��ħ������������ѱ�־


	bool reSendData;  /// ���·���NPC���ɫ���ݸ��Լ�
	bool reSendOther;  /// ���·���NPC���ɫ���ݸ�������

	bool mplock;  ///��mp��������
	bool hplock;  ///��hp��������
	bool splock;  ///��sp��������

	bool afreetMode; /// ��ħɱ���⣨���˱�����
	bool angelMode;  /// ��ʹ�޵У����ڶ�ħ,��������

	bool isPhysicBang; /// �Ƿ�������
	bool isMagicBang; /// �Ƿ�ħ������
	bool isHPhysicBang; /// �Ƿ�������
	bool isHMagicBang; /// �Ƿ�ħ������

	bool assault; ///���

				  //sky ������ɫս��״̬ begin
	bool Daggerflag;	//sky ذ�������˺���־
	bool Throflag;		//sky Ͷ�����������˺���־
	bool Handsflag;		//sky ˫�����������˺���־
	bool Handflag;		//sky �������������˺���־
	bool Flameflag;		//sky ����ħ�������˺���־
	bool Iceflag;		//sky ��˪ħ�������˺���־
	bool Sacredflag;	//sky ��ʥħ�������˺���־
	bool Darkflag;		//sky �ڰ�ħ�������˺���־
	bool Immolate;		//sky �׼���־

	bool dread;			/// sky �־�
	bool blind;			/// sky ʧ��״̬
	bool frozen;		/// sky ����
	bool repentange;	/// sky ���
	bool Silence;		/// sky ��Ĭ
	bool Coma;			///	sky ����
	bool Exile;			/// sky ����

	bool ImmuneDread;	/// sky ���߿־�״̬
	bool ImmuneFrozen;	/// sky ���߱���״̬
	bool ImmuneSilence;	/// sky ���߳�Ĭ״̬
	bool ImmuneComa;	/// sky ���߻���״̬
	bool ImmuneExile;	/// sky ���߷���״̬
						
	bool Soulflag;

	DWORD BattCampID;
	//sky end

	zPos keepPos;  /// ���漼�ܵĹ���Ŀ���,���ݸ���Ҫʹ�õĹ���
	BYTE keepDir;  /// ���漼�ܵĹ�������,���ݸ���Ҫʹ�õĹ���
	BYTE  lastPkTime; //���PK��־
	DWORD bombskillId; /// ����������Ͷ�ͼ���ID

	BYTE damtohpper;  /// ��ɫ���˺�ת��������ֵ�ļ���;
	BYTE damtohpvalper; /// ��ɫ���˺�ת��������ֵ�İٷֱ�

	std::map<BYTE, BYTE>  _effectState;  /// ����״̬��Ч������
	SceneEntryPk *attackTarget;      /// ������������״̬����Ŀ��


	/**
	* \brief ���ֱ���˺�
	* \param pAtt ������
	* \param dam �˺�
	* \param notify �Ƿ�֪ͨ�ͻ���
	* \return �˺�ֵ
	*/
	virtual SWORD directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify = false);

	/**
	* \brief �ı��ɫ��hp
	* \param hp �����HP
	*/
	virtual void changeHP(const SDWORD &hp) = 0;

	/**
	* \brief �ı��ɫ��sp
	* \param sp �����SP
	*/
	virtual void changeSP(const SDWORD &sp) = 0;

	/**
	* \brief �ı��ɫ��mp
	* \param mp �����MP
	*/
	virtual void changeMP(const SDWORD &mp) = 0;

	/**
	* \brief �������hp
	* \return �������ֵ
	*/
	virtual DWORD getMaxHP() { return 0; }

	/**
	* \brief �������hp
	* \return �������ֵ
	*/
	virtual DWORD getBaseMaxHP() { return 0; }

	/**
	* \brief �������mp
	* \return �������ֵ
	*/
	virtual DWORD getMaxMP() { return 0; }

	/**
	* \brief �������mp
	* \return �������ֵ
	*/
	virtual DWORD getBaseMaxMP() { return 0; }

	/**
	* \brief �������sp
	* \return �������ֵ
	*/
	virtual DWORD getMaxSP() { return 0; }

	/**
	* \brief ��õ�ǰħ��������
	* \return ħ��������
	*/
	virtual DWORD getMaxMDamage() { return 0; }

	/**
	* \brief ��õ�ǰ��������
	* \return ��������
	*/
	virtual DWORD getMaxPDamage() { return 0; }

	/**
	* \brief ��õ�ǰ���������
	* \return ���������
	*/
	virtual DWORD getPDefence() { return 0; }

	/**
	* \brief ��õ�ǰħ��������
	* \return ħ��������
	*/
	virtual DWORD getMDefence() { return 0; }

	/**
	* \brief ��������hp
	*/
	virtual void changeAndRefreshHMS(bool lock = true, bool sendData = true) {}

	/**
	* \brief �ڱ��Լ�����֮ǰ�Ĵ���,����,װ����Ĵ���,������Ч�����жϵ�
	* \param pUser ������
	* \param rev ���ι����Ĵ���ָ��
	* \param physics �Ƿ�������
	* \param good Ϊtrue�����,falseҪ�жϻر���
	* \return trueΪ��ι�������Ч��,falseΪһ����Ч�Ĺ���
	*/
	virtual bool preAttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics = true, const bool good = false) = 0;

	/**
	* \brief ��ɫ������
	* \param pUser ������
	* \param rev ���ι����Ĵ�����Ϣ
	* \param physics �Ƿ�������
	* \return trueΪ��ι�������Ч��,falseΪһ����Ч�Ĺ���
	*/
	virtual bool AttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics = true, SWORD rangDamageBonus = 0);
	/**
	* \brief �ж��Ƿ��ǵ���
	* \return true �� false ����
	*/
	virtual int isEnemy(SceneEntryPk *entry, bool notify = false, bool good = false) = 0;

	/**
	* \brief �ж��Ƿ�ɹ���
	* \return true �� false ����
	*/
	virtual bool isBugbear() { return true; }

	/**
	* \brief ��ȡ�Լ�������,һ�����NPC����,Player���������Լ�
	* \return NULL�������˵Ķ���ָ��
	*/
	virtual SceneEntryPk *getMaster() = 0;

	/**
	* \brief �õ����ϲ������
	*
	* \return ����
	*/
	virtual SceneEntryPk *getTopMaster() = 0;

	/**
	* \brief �ý�ɫ����
	* \param dwTempID �����ߵ���ʱID
	*/
	virtual void toDie(const DWORD &dwTempID) = 0;

	/**
	* \brief ����Ļ������ƶ�
	*/
	virtual void goToRandomScreen() {};

	/**
	* \brief ����Ļ�ڶ����ƶ�
	*/
	virtual void jumpTo(zPos &newPos) {};

	/**
	* \brief ֪ͨ�ͻ�������ֵ�ı仯
	*/
	virtual void attackRTHpAndMp() {};

	/**
	* \brief �жϽ�ɫ�Ƿ�����
	*/
	virtual bool isDie() = 0;

	/**
	* \brief ��ȡ��ɫ�ļ���
	*/
	virtual DWORD getLevel() const = 0;

	/**
	* \brief ��ȡ���е���
	* \return ���ظ����͵����е���
	*/
	virtual DWORD getFiveType() { return 0; }

	/**
	* \brief ��Ҫ��ְҵ����,��������ʹ�õļ�������
	*/
	virtual bool needType(const DWORD &needtype) = 0;

	/**
	* \brief �Ƿ��иü�����Ҫ������
	* \return true �� false û��
	*/
	virtual bool needWeapon(DWORD skillid) = 0;

	/**
	* \brief �Ƿ�Pk����
	* \param other PK�����
	* \return true �� false ��
	*/
	virtual bool isPkZone(SceneEntryPk *other = NULL) = 0;

	/**
	* \brief ������Ʒ�����ͷ���
	* \param object ������Ʒ������
	* \param num ������Ʒ������
	* \return true ���ĳɹ� false ʧ��
	*/
	virtual bool reduce(const DWORD &object, const BYTE num) = 0;

	/**
	* \brief ����������Ʒ�Ƿ��㹻
	* \param object ������Ʒ������
	* \param num ������Ʒ������
	* \return true �㹻 false ����
	*/
	virtual bool checkReduce(const DWORD &object, const BYTE num) = 0;
	/**
	* \brief ��ȡװ���˺��ӳ�
	* \return �˺��ӳ�
	*/
	virtual WORD getDamageBonus() { return 0; }

	virtual void showCurrentEffect(const WORD &state, bool isShow, bool notify = true) = 0;

};

#endif


