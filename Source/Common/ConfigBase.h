#ifndef __CONFIG_BASE_H_
#define __CONFIG_BASE_H_

#include "SrvEngine.h"

#pragma pack(push,1)

// CharType
struct CharTypeBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD  field0;		// ���(����) 
	char   field1[32];	// ���� 
	DWORD  field2;		// ����1 
	DWORD  field3;		// ����2 
	DWORD  field4;		// ����3 
	DWORD  field5;		// ����4 
};

struct zCharTypeB : zEntry
{
	DWORD id;			// ����ID
	std::string name;     	// ���� 
	DWORD skill1;		// ����1 
	DWORD skill2;		// ����2 
	DWORD skill3;		// ����3 
	DWORD skill4;		// ����4 
	inline uint64_t GetID() {return id;}
	inline uint64_t GetTempID() { return _entry_tempid; }
	inline const std::string& GetName() { return name; }
	void fill(const CharTypeBase& base)
	{
		id = base.field0;
		name = base.field1;
		skill1 = base.field2;
		skill2 = base.field3;
		skill3 = base.field4;
		skill4 = base.field5;
	}

	zCharTypeB() :zEntry()
	{
		id = skill1 = skill2 = skill3 = skill4 = 0;
	}
};


// CharLevel
struct CharLevelBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD field0;		// ��� 
	DWORD field1;		// ��ɫ����  
	DWORD field2;		// �ȼ� 
	DWORD field3;		// �������� 
	DWORD field4;		// �������� 
	DWORD field5;		// �����ظ� 
	DWORD field6;		// ŭ������ 
	DWORD field7;		// ŭ���ظ� 
	DWORD field8;		// �չ� 
	DWORD field9;		// �շ� 
	DWORD field10;		// ���� 
	DWORD field11;		// ���� 
	DWORD field12;		// ������:�ٷݱ� 
	DWORD field13;		// �����˺� 
	DWORD field14;		// ���� 
	DWORD field15;		// ��ֵ 
	DWORD field16;		// ����:�ٷݱ� 
	DWORD field17;		// ����:�ٷݱ� 
	DWORD field18;		// ���� 
	DWORD field19;		// ���� 
}; 

struct zCharLevelB : zEntry
{
	DWORD id;
	DWORD type;		// ��ɫ���� 
	DWORD level;		// �ȼ� 
	DWORD exp;		// �������� 
	DWORD hp;		// �������� 
	DWORD hpRecover;		// �����ظ� 
	DWORD mp;		// ŭ������ 
	DWORD mpRecover;		// ŭ���ظ� 
	DWORD pa;		// �﹥ 
	DWORD pd;		// ��� 
	DWORD ma;		// ħ�� 
	DWORD md;		// ħ�� 
	DWORD criteRate;		// ������:�ٷݱ� 
	DWORD criteVal;		// �����˺� 
	DWORD tenacity;		// ����:�ٷݱ� 
	DWORD block;		// �� 
	DWORD dodge;		// ����:�ٷݱ� 
	DWORD hit;		// ����:�ٷݱ� 
	DWORD as;		// ���� 
	DWORD ms;		// ���� 

	void fill(const CharLevelBase& base)
	{
		id = base.field0;
		type = base.field1;
		level = base.field2;
		exp = base.field3;
		hp = base.field4;
		hpRecover = base.field5;
		mp = base.field6;
		mpRecover = base.field7;
		pa = base.field8;
		pd = base.field9;
		ma = base.field10;
		md = base.field11;
		criteRate = base.field12;
		criteVal = base.field13;
		tenacity = base.field14;
		block = base.field15;
		dodge = base.field16;
		hit = base.field17;
		as = base.field18;
		ms = base.field19;
	}

	zCharLevelB() : zEntry()
	{
		id = type = level = exp = hp = hpRecover = mp = mpRecover = 0;
		pa = pd = ma = md = criteRate = criteVal = tenacity = block = dodge = hit = as = ms = 0;
	}
};


//------------------------------------
// NpcBase
//------------------------------------
struct NpcBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD  field0;		// ��� 
	char   field1[32];	// ���� 
	DWORD  field2;		// ���� 
	DWORD  field3;		// �ȼ� 
	DWORD  field4;		// ����ֵ 
	DWORD  field5;		// ����ֵ 
	DWORD  field6;		// ���� 
	DWORD  field7;		// ���� 
	DWORD  field8;		// ���� 
	DWORD  field9;		// ���� 
	DWORD  field10;		// ���� 
	DWORD  field11;		// ��ɫ 
	DWORD  field12;		// ��������1 
	DWORD  field13;		// ��������2 
	DWORD  field14;		// AI 
	DWORD  field15;		// �ƶ���� 
	DWORD  field16;		// ������� 
	DWORD  field17;		// �������� 
	DWORD  field18;		// ��С���� 
	DWORD  field19;		// ��󹥻� 
	DWORD  field20;		// ��С���� 
	DWORD  field21;		// ��󷨹� 
	DWORD  field22;		// ��С��� 
	DWORD  field23;		// ������ 
	DWORD  field24;		// ��С���� 
	DWORD  field25;		// ��󷨷� 
	DWORD  field26;		// ����� 
	DWORD  field27;		// ������ 
	DWORD  field28;		// PK����1 
	DWORD  field29;		// PK����2 
	DWORD  field30;		// PK����3 
	DWORD  field31;		// PK����4 
	DWORD  field32;		// ����1 
	DWORD  field33;		// ����2 
	DWORD  field34;		// ����3 
	DWORD  field35;		// ����4 
	DWORD  field36;		// �������� 
	DWORD  field37;		// ���е��� 
	char  field38[4096];// Я����Ʒ 
};

/**
* \brief Npc����������� 
*
*/
struct zNpcB : public zEntry
{
	DWORD id;
	std::string name;   // ���� 
	DWORD kind;        	// ���� 
	DWORD level;       	// �ȼ� 
	DWORD hp;       	// ����ֵ 
	DWORD exp;      	// ����ֵ 
	DWORD strong;       // ���� 
	DWORD intellect;	// ���� 
	DWORD flexible;     // ���� 
	DWORD spirit;		// ���� 
	DWORD physique;     // ���� 
	DWORD color;        // ��ɫ 
	DWORD backup1;  	// ��������1 
	DWORD backup2; 		// ��������2 
	DWORD ai;			// AI  
	DWORD move_time;	// �ƶ����  
	DWORD attack_time;  // �������  
	DWORD attack_type;  // �������� 
	DWORD physicAttackMin;	// ��С���� 
	DWORD physicAttackMax;	// ��󹥻�  
	DWORD spellAttackMin;	// ��С���� 
	DWORD spellAttackMax;	// ��󷨹� 
	DWORD physicDefendMin;	// ��С���    
	DWORD physicDefendMax;	// ������ 
	DWORD spellDefendMin;	// ��С����   	
	DWORD spellDefendMax;	// ��󷨷� 
	DWORD dodge;			// ����� 
	DWORD hit;				// ������ 
	DWORD pk1;				// PK����1 
	DWORD pk2;				// PK����2 
	DWORD pk3;				// PK����3 
	DWORD pk4;				// PK����4    	
	DWORD skill1;			// ����1 
	DWORD skill2;      		// ����2 
	DWORD skill3;  			// ����3 
	DWORD skill4;    		// ����4 
	DWORD fivelineType;		// �������� 
	DWORD fivelinePoint;	// ���е��� 
							//char carryObjs[256];	// Я����Ʒ 

	void fill(const NpcBase &base)
	{
		id = base.field0;
		kind = base.field2;
		level = base.field3;
		hp = base.field4;
		exp = base.field5;
		strong = base.field6;
		intellect = base.field7;
		flexible = base.field8;
		spirit = base.field9;
		physique = base.field10;
		color = base.field11;
		backup1 = base.field12;
		backup2 = base.field13;
		ai = base.field14;
		move_time = base.field15;
		attack_time = base.field16;
		attack_type = base.field17;
		physicAttackMin = base.field18;
		physicAttackMax = base.field19;
		spellAttackMin = base.field20;
		spellAttackMax = base.field21;
		physicDefendMin = base.field22;
		physicDefendMax = base.field23;
		spellDefendMin = base.field24;
		spellDefendMax = base.field25;
		dodge = base.field26;
		hit = base.field27;
		pk1 = base.field28;
		pk2 = base.field29;
		pk3 = base.field30;
		pk4 = base.field31;
		skill1 = base.field32;
		skill2 = base.field33;
		skill3 = base.field34;
		skill4 = base.field35;
		fivelineType = base.field36;
		fivelinePoint = base.field37;
		//strncpy(name, base.field1, 32);
	}

	zNpcB() : zEntry()
	{
		id = kind = level = hp = exp = strong = intellect = flexible = spirit = physique = color = 0;
		backup1 = backup2 = ai = move_time = attack_time = attack_type = 0;
		physicAttackMin = physicAttackMax = spellAttackMin = spellAttackMax = physicDefendMin = physicDefendMax = spellDefendMin = spellDefendMax = 0;
		dodge = hit = pk1 = pk2 = pk3 = pk4 = skill1 = skill2 = skill3 = skill4 = fivelineType = fivelinePoint = 0;
	}

};

struct ShopBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	int32_t  field0;		// ��� 
	char   field1[32];	// ���� 
	int32_t  field2;		// ���� 
	int32_t  field3;		// λ�� 
	int32_t  field4;		// ����ID 
	int32_t  field5;		// �������� 
	int32_t  field6;		// ��Ǯ���� 
	int32_t  field7;		// ��Ǯֵ  
	int32_t  field8;		// ��������ȼ� 
};

/**
* \brief Npc����������� 
*
*/
struct zShopB : public zEntry
{
	int32_t id;
	std::string name;     	// ���� 
	int32_t category;     // ���� 
	int32_t position;		// λ��  
	int32_t itemID;       	// �ȼ� 
	int32_t itemNum;       	// ����ֵ 
	int32_t sellMoneyType;      	// ����ֵ 
	int32_t sellMoneyValue;       // ���� 
	int32_t needLevel;	// �ȼ�  
	void fill(const ShopBase &shop)
	{
		id = shop.field0;
		category = shop.field2;
		position = shop.field3;
		itemID = shop.field4;
		itemNum = shop.field5;
		sellMoneyType = shop.field6;
		sellMoneyValue = shop.field7;
		needLevel = shop.field8;
	}
	zShopB() : zEntry()
	{
		id = category = position = itemID = itemNum = sellMoneyType = sellMoneyValue = needLevel = 0;
	}
};


// ���߱� 
struct ItemBase 
{
	const DWORD getUniqueID() const
	{
		return field0;
	}

	DWORD field0;
	string field1; // ���� 
	DWORD field2;	// ������ 
	DWORD field3;	// ����Ǯ���� 
	DWORD field4;	// ����Ǯ���� 
	DWORD field5;	// ��ǹ��� 
	DWORD field6;	// ���������� 
	string field7;	// ʹ��Ч��1 
	string field8;	// ʹ��Ч��2 
	DWORD field9;	// װ��λ�� 
	DWORD field10;  // Ʒ�� 
	DWORD field11;  // �ȼ� 
	DWORD field12;	// ��������  
	DWORD field13;	// ��������
	DWORD field14;	// HP�ָ� 
	DWORD field15;	// MP�ָ� 
	DWORD field16;	// �﹥ 
	DWORD field17;	// ��� 
	DWORD field18;	// ���� 
	DWORD field19;	// ���� 
	DWORD field20;  // ����ֵ 
	DWORD field21;	// ������ 
	DWORD field22;	// ������ 
	DWORD field23;	// ��ֵ 
	DWORD field24;	// ������ 
	DWORD field25;	// ������ 
	DWORD field26;	// ���� 
	DWORD field27;	// ���� 
	//DWORD field28;	// չʾͼƬ 
	//DWORD field29;	// ���� 
};

struct zItemB : zEntry
{

	enum ItemTye
	{
		TYPE_NONE = 0,
		TYPE_ITEM,	/* ��ͨ���� */
		TYPE_EQUIP, /* װ�� */
		TYPE_QUEST, /* ������� */
		TYPE_PKING, /* PK��ʹ�õ��� */
	};

	struct Effect
	{
		DWORD target;
		DWORD funcType;
		DWORD funcID;
		DWORD funcVal;
	};

	/* ʹ�ö��� */
	enum EffectTarget
	{
		TARGET_MINE = 1,
		TARGET_OPPOSING,
	};

	/* Ч������ */
	enum EffectFunc
	{
		FUNC_MONEY, 
		FUNC_EXP,
		FUNC_PKVAL,
		FUNC_BUFF,
		FUNC_PET,
	};

	/* Ч�������� */
	enum EffectID
	{
		FUNC_ID_MONEY_GOLD = 1,
		FUNC_ID_MONEY_SILVER = 2,
		FUNC_ID_MONEY_COPPER = 3,
	};


	//DWORD field0;
	//char field1[32]; // ���� 
	DWORD id;	// 
	std::string name;
	DWORD mainType;	// ������ 
	DWORD sellType;	// ����Ǯ���� 
	DWORD sellVal;	// ����Ǯ���� 
	DWORD flag;	// ��ǹ��� 
	DWORD amount;	// ���������� 
	Effect effect1;	// ʹ��Ч��1 
	Effect effect2;	// ʹ��Ч��2 
	DWORD equipPos;	// װ��λ�� 
	DWORD quilty;  // Ʒ�� 
	DWORD useLevel;  // �ȼ� 
	EntryPkValBase pkVal;

	void fill(const ItemBase& base)
	{
		id = base.field0;
		mainType = base.field2;
		sellType = base.field3;
		sellVal = base.field4;
		flag = base.field5;
		amount = base.field6;

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field7, ",-;");
			if (obs.size() != 4)
			{
				ASSERT(0);
				return;
			}

			effect1.target = atoi(obs[0].c_str());
			effect1.funcType = atoi(obs[1].c_str());
			effect1.funcID = atoi(obs[2].c_str());
			effect1.funcVal = atoi(obs[3].c_str());
		}

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field8, ",-;");
			if (obs.size() != 4)
			{
				ASSERT(0);
				return;
			}

			effect2.target = atoi(obs[0].c_str());
			effect2.funcType = atoi(obs[1].c_str());
			effect2.funcID = atoi(obs[2].c_str());
			effect2.funcVal = atoi(obs[3].c_str());
		}

		equipPos = base.field9;
		quilty = base.field10;
		useLevel = base.field11;

		pkVal.nRedMax = base.field12;				// �������� 
		pkVal.nBlueMax = base.field13;				// ��������
		pkVal.nRedRecover = base.field14;		// HP�ָ� 
		pkVal.nBlueRecover = base.field15;			// MP�ָ� 
		pkVal.nPhysicAttack = base.field16;			// �﹥ 
		pkVal.nPhysicDefend = base.field17;		// ��� 
		pkVal.nSpellAttack = base.field18;		// ���� 
		pkVal.nSpellDefend = base.field19;			// ���� 
		pkVal.nBaojilv = base.field20;				// ����ֵ 
		pkVal.nBaoji = base.field21;				// ������ 
		pkVal.nGedanglv = base.field22;				// ������ 
		pkVal.nGedang = base.field23;				// ��ֵ 
		pkVal.nShanbilv = base.field24;			// ������ 
		pkVal.nMingzhonglv = base.field25;			// ������ 
		pkVal.nAttackSpeed = base.field26;		// ���� 
		pkVal.nMoveSpeed = base.field27;	// ���� 

	}
	zItemB(): zEntry()
	{

	}
};


//------------------------------------
// SkillBase
//------------------------------------
/**
* \brief ���ݼ������ͺ͵ȼ�����һ����ʱΨһ���
*
*/
#define skill_hash(type,level) ((type - 1) * 100 + level)


struct SkillBase
{
	const DWORD getUniqueID() const
	{
		return field0;
	}
	DWORD field0;		// ��� 
	char field1[32];	// ���� 
	DWORD field2;		// ���� 
	DWORD field3;		// �˺����� 
	string field4;	// Ч��1 
	string field5;	// Ч��2 
	string field6;	// �������� 
	string field7;	// ��������Ӽ���  
	string field8;	// ����  

};



struct zSkillB : zEntry
{

	struct SkillEffect
	{
		DWORD batttype;
		DWORD emitobj;		// ʩ�Ŷ��� 
		DWORD effectVal;	// ����ֵ 
		DWORD effectValInc;	// ����ֵ����ȼ��йأ� 
		DWORD effectRate;	// ʩ�Ÿ��� 
		DWORD effectRateInc;// ʩ�Ÿ�������ֵ 
	};

	struct SkillUplevel
	{
		DWORD uptype;
		DWORD upid;
		DWORD upnum;
		DWORD upnumInc;
	};

	struct SkillSub
	{
		DWORD needLevel;
		DWORD subSkillID;
		DWORD subSkillLv;
	};
	DWORD id;
	std::string name[32];
	DWORD type;
	DWORD hurttype;

	SkillEffect effect1;
	SkillEffect effect2;
	SkillUplevel uplevel;
	SkillSub subSkill;

	void fill(const SkillBase& base)
	{
		id = base.field0;
		type = base.field2;
		hurttype = base.field3;

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field4, ",-;");
			if (obs.size() != 6)
			{
				ASSERT(0);
				return;
			}

			effect1.batttype = atoi(obs[0].c_str());
			effect1.emitobj = atoi(obs[1].c_str());
			effect1.effectVal = atoi(obs[2].c_str());
			effect1.effectValInc = atoi(obs[3].c_str());
			effect1.effectRate = atoi(obs[4].c_str());
			effect1.effectRateInc = atoi(obs[5].c_str());
		}

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field5, ",-;");
			if (obs.size() != 6)
			{
				ASSERT(0);
				return;
			}

			effect2.batttype = atoi(obs[0].c_str());
			effect2.emitobj = atoi(obs[1].c_str());
			effect2.effectVal = atoi(obs[2].c_str());
			effect2.effectValInc = atoi(obs[3].c_str());
			effect2.effectRate = atoi(obs[4].c_str());
			effect2.effectRateInc = atoi(obs[5].c_str());
		}


		{
			std::vector<std::string> obs;
			stringtok(obs, base.field6, ",-;");
			if (obs.size() != 4)
			{
				ASSERT(0);
				return;
			}

			uplevel.uptype = atoi(obs[0].c_str());
			uplevel.upid = atoi(obs[1].c_str());
			uplevel.upnum = atoi(obs[2].c_str());
			uplevel.upnumInc = atoi(obs[3].c_str());
		}

		{
			std::vector<std::string> obs;
			stringtok(obs, base.field7, ",-;");
			if (obs.size() != 3)
			{
				ASSERT(0);
				return;
			}

			subSkill.needLevel = atoi(obs[0].c_str());
			subSkill.subSkillID = atoi(obs[1].c_str());
			subSkill.subSkillLv = atoi(obs[2].c_str());
		}


	}

	zSkillB() :zEntry()
	{

	}
};

//struct SkillBase
//{
//	const DWORD getUniqueID() const
//	{
//		return skill_hash(dwField0, dwField2);
//	}
//
//	DWORD  dwField0;      // ����ID
//	char  strField1[32];    // ��������
//	DWORD  dwField2;      // ���ܵȼ�
//	DWORD  dwField3;      // ����ϵ��
//	DWORD  dwField4;      // ��������
//	DWORD  dwField5;      // ��Ҫ���߼��ܵ���
//	DWORD  dwField6;      // ǰ�Ἴ��һ
//	DWORD  dwField7;      // ǰ�Ἴ��һ�ȼ�
//	DWORD  dwField8;      // ǰ�Ἴ�ܶ�
//	DWORD  dwField9;      // ǰ�Ἴ�ܶ��ȼ�
//	DWORD  dwField10;      // ǰ�Ἴ����
//	DWORD  dwField11;      // ǰ�Ἴ�����ȼ�
//	DWORD  dwField12;      // ���ʱ��
//	DWORD  dwField13;      // ������ʽ
//	DWORD  dwField14;      // �ܷ�����ʹ��
//	DWORD  dwField15;      // ��Ҫ��Ʒ
//	char  strField16[128];  // ��Ҫ����
//	DWORD  dwField17;      // ��������ֵ
//	DWORD  dwField18;      // ���ķ���ֵ
//	DWORD  dwField19;      // ��������ֵ
//	DWORD  dwField20;      // �˺��ӳ�
//	char  strField21[1024];  // Ч��
//	DWORD  dwField22;      // ������Ʒ����
//	DWORD  dwField23;      // ��Ʒ��������
//};//���� SkillBase �ɹ����� 1 ����¼
//
#define BENIGNED_SKILL_STATE 2
#define BAD_SKILL_STATE 4
#define NONE_SKILL_STATE 1 

struct SkillElement
{
	SkillElement()
	{
		id = 0;
		value = 0;
		percent = 0;
		time = 0;
		state = 0;
	}
	union {
		struct {
			DWORD id;
			DWORD percent;
			DWORD value;
			DWORD time;
			DWORD state;
		};
		DWORD element[5];
	};
	static SkillElement *create(SkillElement elem);
};
struct SkillStatus
{
	SkillStatus()
	{
		for (int i = 0; i < (int)(sizeof(status) / sizeof(WORD)); i++)
		{
			status[i] = 0;
		}
	}
	union {
		struct {
			WORD id;//����id
			WORD target;//Ŀ��
			WORD center;//���ĵ�
			WORD range;//��Χ
			WORD mode;//����ģʽ
			WORD clear;//�ܷ����
			WORD isInjure;//�Ƿ���Ҫ�˺�����
		};
		WORD status[7];
	};
	std::vector<SkillElement> _StatusElementList;
};
//struct zSkillB : public zEntry
//{
//	bool has_needweapon(const WORD weapontype) const
//	{
//		std::vector<WORD>::const_iterator iter;
//		if (weaponlist.empty()) return true;
//		for (iter = weaponlist.begin(); iter != weaponlist.end(); iter++)
//		{
//			if (*iter == weapontype) return true;
//		}
//		return false;
//	}
//
//	bool set_weaponlist(const char *data)
//	{
//		weaponlist.clear();
//		std::vector<std::string> v_fir;
//		stringtok(v_fir, data, ":");
//		for (std::vector<std::string>::iterator iter = v_fir.begin(); iter != v_fir.end(); iter++)
//		{
//			WORD weaponkind = (WORD)atoi(iter->c_str());
//			weaponlist.push_back(weaponkind);
//		}
//		return true;
//	}
//
//	bool set_skillState(const char *data)
//	{
//		skillStatus.clear();
//		std::vector<std::string> v_fir;
//		stringtok(v_fir, data, ".");
//		for (std::vector<std::string>::iterator iter = v_fir.begin(); iter != v_fir.end(); iter++)
//		{
//			//Zebra::logger->debug("%s",iter->c_str());
//			std::vector<std::string> v_sec;
//			stringtok(v_sec, iter->c_str(), ":");
//			/*
//			if (v_sec.size() != 2)
//			{
//			return false;
//			}
//			// */
//			SkillStatus status;
//			std::vector<std::string>::iterator iter_1 = v_sec.begin();
//			std::vector<std::string> v_thi;
//			stringtok(v_thi, iter_1->c_str(), "-");
//			if (v_thi.size() != 7)
//			{
//				//Zebra::logger->debug("����!=7");
//				continue;
//				//return false;
//			}
//			std::vector<std::string>::iterator iter_2 = v_thi.begin();
//			for (int i = 0; i < 7; i++)
//			{
//				status.status[i] = (WORD)atoi(iter_2->c_str());
//				//Zebra::logger->debug("status.status[%ld]=%ld",i,status.status[i]);
//				iter_2++;
//			}
//			iter_1++;
//			if (iter_1 == v_sec.end())
//			{
//				//Zebra::logger->debug("�ղ���");
//				skillStatus.push_back(status);
//				continue;
//			}
//			std::vector<std::string> v_fou;
//			stringtok(v_fou, iter_1->c_str(), ";");
//			std::vector<std::string>::iterator iter_3 = v_fou.begin();
//			for (; iter_3 != v_fou.end(); iter_3++)
//			{
//				std::vector<std::string> v_fiv;
//				stringtok(v_fiv, iter_3->c_str(), "-");
//				if (v_fiv.size() != 5)
//				{
//					//Zebra::logger->debug("Ԫ�ظ�������");
//					continue;
//					//return false;
//				}
//				std::vector<std::string>::iterator iter_4 = v_fiv.begin();
//				SkillElement element;
//				for (int i = 0; i < 5; i++)
//				{
//					element.element[i] = (DWORD)atoi(iter_4->c_str());
//					//Zebra::logger->debug("element.element[%u]=%u",i,element.element[i]);
//					iter_4++;
//				}
//				status._StatusElementList.push_back(element);
//			}
//			skillStatus.push_back(status);
//		}
//		return true;
//	}
//	DWORD  skillid;            //����ID
//	DWORD  level;              //���ܵȼ�
//	DWORD  kind;              //����ϵ��
//	DWORD  subkind;            //��������
//	DWORD  needpoint;            //��Ҫ���߼��ܵ���
//	DWORD  preskill1;            //ǰ�Ἴ��1
//	DWORD  preskilllevel1;          //ǰ�Ἴ�ܼ���1
//	DWORD  preskill2;            //ǰ�Ἴ��2
//	DWORD  preskilllevel2;          //ǰ�Ἴ�ܼ���2
//	DWORD  preskill3;            //ǰ�Ἴ��3
//	DWORD  preskilllevel3;          //ǰ�Ἴ�ܼ���3
//	DWORD  dtime;              //���ʱ��
//	DWORD  usetype;            //������ʽ
//	DWORD  ride;              //�ɷ�����ʹ��
//	DWORD  useBook;            //��Ҫ��Ʒ
//	DWORD  spcost;              //��������ֵ
//	DWORD  mpcost;              //���ķ���ֵ
//	DWORD  hpcost;              //��������ֵ
//	DWORD  damnum;              //�˺��ӳ�
//	DWORD  objcost;            //������Ʒ����
//	DWORD  objnum;              //������Ʒ����
//	std::vector<SkillStatus> skillStatus;  //Ч��
//	std::vector<WORD> weaponlist;      //�����б�
//
//
//
//	void fill(const SkillBase &data)
//	{
//		id = skill_hash(data.dwField0, data.dwField2);
//		skillid = data.dwField0;                //����ID
//		strncpy(name, data.strField1, MAX_NAMESIZE);
//		level = data.dwField2;          //���ܵȼ�
//		kind = data.dwField3;          //����ϵ��
//		subkind = data.dwField4;          //��������
//		needpoint = data.dwField5;          //��Ҫ���߼��ܵ���
//		preskill1 = data.dwField6;          //ǰ�Ἴ��1
//		preskilllevel1 = data.dwField7;;          //ǰ�Ἴ�ܼ���1
//		preskill2 = data.dwField8;          //ǰ�Ἴ��2
//		preskilllevel2 = data.dwField9;          //ǰ�Ἴ�ܼ���2
//		preskill3 = data.dwField10;          //ǰ�Ἴ��3
//		preskilllevel3 = data.dwField11;          //ǰ�Ἴ�ܼ���3
//		dtime = data.dwField12;          //���ʱ��
//		usetype = data.dwField13;          //������ʽ
//		ride = data.dwField14;          //�ɷ�����ʹ��
//		useBook = data.dwField15;          //ѧϰ��Ҫ��Ʒ
//		set_weaponlist(data.strField16);          //��Ҫ����
//		spcost = data.dwField17;          //��������ֵ
//		mpcost = data.dwField18;          //���ķ���ֵ
//		hpcost = data.dwField19;          //��������ֵ
//		damnum = data.dwField20;          //�˺��ӳ�
//		set_skillState(data.strField21);
//		objcost = data.dwField22;          //������Ʒ����
//		objnum = data.dwField23;          //������Ʒ����
//	}
//
//
//	zSkillB() : zEntry()
//	{
//		id = 0;
//		skillid = 0;
//		bzero(name, sizeof(name));        //˵��
//		level = 0;          //���ܵȼ�
//		kind = 0;          //����ϵ��
//		subkind = 0;          //��������
//		needpoint = 0;          //��Ҫ���߼��ܵ���
//		preskill1 = 0;          //ǰ�Ἴ��1
//		preskilllevel1 = 0;          //ǰ�Ἴ�ܼ���1
//		preskill2 = 0;          //ǰ�Ἴ��2
//		preskilllevel2 = 0;          //ǰ�Ἴ�ܼ���2
//		preskill3 = 0;          //ǰ�Ἴ��3
//		preskilllevel3 = 0;          //ǰ�Ἴ�ܼ���3
//		dtime = 0;          //���ʱ��
//		usetype = 0;          //������ʽ
//		ride = 0;          //�ɷ�����ʹ��
//		useBook = 0;          //��Ҫ��Ʒ
//		spcost = 0;          //��������ֵ
//		mpcost = 0;          //���ķ���ֵ
//		hpcost = 0;          //��������ֵ
//		damnum = 0;          //�˺��ӳ�
//		objcost = 0;          //������Ʒ����
//		objnum = 0;          //������Ʒ����
//	}
//
//};

struct LiveSkillBase {

	const DWORD getUniqueID() const
	{
		return ((0xffff & dwField11) << 16) | (0xffff & dwField0);
	}

	DWORD  dwField0;    // ����ID
	char  strField1[64];    // ��������
	DWORD  dwField2;    // ��Ҫ����
	DWORD  dwField3;    // ��ʼ����
	DWORD  dwField4;    // ��Ӧͼ��
	DWORD  dwField5;    // ���
	DWORD  dwField6;    // ������������
	DWORD  dwField7;    // �ɷ�����
	DWORD  dwField8;    // ���׼���
	DWORD  dwField9;    // ǰ�Ἴ��ID
	DWORD  dwField10;    // ����ǰ�Ἴ�ܵȼ�
	DWORD  dwField11;    // ���ܵȼ�
	char  strField12[32];    // ���ܳƺ�
	char  strField13[256];    // �����Ʒ
};

struct zLiveSkillB : public zEntry
{
	enum {
		MAX_EXP_BONUS = 30,
		MIN_POINT_BONUS = 1,
		MAX_POINT_BONUS = 3,
		WORKING_TIME = 6,
		MAX_LEVEL = 30,
	};

	//DWORD skill_id; //���ܱ�ʶ
	//DWORD level; //���ܵȼ�
	//WORD should be enough
	DWORD id; //���ܱ�ʶ
	WORD skill_id; //���ܱ�ʶ
	WORD level; //���ܵȼ�
	DWORD point; //�������輼�ܵ�
	DWORD weapon_kind; //��������
					   //std::string name; //��������
	std::string title; //�ƺ�
	bool orig; //��ʼ����
	bool upgrade; //�ܷ�����
	DWORD kind; //�������
	DWORD basic_skill_id; //ǰ�Ἴ��id
	DWORD basic_skill_level; //ǰ�Ἴ�ܵȼ�]
	DWORD up_skill_id; //���׼���id
	DWORD map_kind;

	class ITEM
	{
	public:
		DWORD item; //�����Ʒ
		DWORD odds;  //����
		DWORD min_number; //��С����
		DWORD max_number; //�������

		ITEM(const std::string& odds_, const std::string& item_, const std::string& number_) : item(atoi(item_.c_str())), odds(atoi(odds_.c_str())), min_number(0), max_number(0)
		{
			std::string::size_type pos = 0;
			if ((pos = number_.find("-")) != std::string::npos) {

				min_number = atoi(number_.substr(0, pos).c_str());
				max_number = atoi(number_.substr(pos + strlen("-")).c_str());
			}
			//if (item) Zebra::logger->debug("�Ͷ������Ʒ����:ID(%d),����(%d),����(%d-%d)",item,odds,min_number,max_number);
		}
	};

	typedef std::vector<ITEM> ITEMS;
	ITEMS items;

	BYTE min_point_bonus; //��С���Ӽ��ܵ�
	BYTE max_point_bonus; //������Ӽ��ܵ�
	BYTE exp_bonus; //��������
	BYTE max_level; //���ȼ�

	zLiveSkillB() : zEntry(), skill_id(0), level(0), point(0), weapon_kind(0),/*name("δ֪"),*/ title(""), orig(false), upgrade(false),
		kind(1), basic_skill_id(0), basic_skill_level(0), up_skill_id(0), map_kind(0),
		min_point_bonus(MIN_POINT_BONUS), max_point_bonus(MAX_POINT_BONUS), exp_bonus(MAX_EXP_BONUS),
		max_level(MAX_LEVEL)
	{

	}

	void fill(const LiveSkillBase& base)
	{
		skill_id = 0xffff & base.dwField0;
		//name = base.strField1;
		weapon_kind = base.dwField2;
		orig = (base.dwField3 == 1) ? true : false;
		map_kind = base.dwField4;
		kind = base.dwField5;
		point = base.dwField6;
		upgrade = (base.dwField7 == 1) ? true : false;
		up_skill_id = base.dwField8;
		basic_skill_id = base.dwField9;
		basic_skill_level = base.dwField10;
		level = 0xffff & base.dwField11;
		title = base.strField12;
		init_items(base.strField13);

		id = (level << 16) | skill_id;
	}

	void init_items(const std::string& item_list)
	{
		items.clear();
		Split<Parse3> p;
		p(item_list, items, ";", ":");

	}

};




extern zDataBM<zCharTypeB, CharTypeBase> &chartypebm;
extern zDataBM<zCharLevelB, CharLevelBase> &charlevelbm;
extern zDataBM<zNpcB, NpcBase> &npcbm;
extern zDataBM<zShopB, ShopBase> &shopbm;
extern zDataBM<zSkillB, SkillBase> &skillbm;
extern zDataBM<zItemB, ItemBase> &itembm;

//extern zDataBM<zCharacterB,CharacterBase> &characterbm;
//extern zDataBM<zExperienceB, ExperienceBase> &experiencebm;
//extern zDataBM<zHonorB, HonorBase> &honorbm;
//extern zDataBM<zSkillB, SkillBase> &skillbm;
//extern zDataBM<zLiveSkillB, LiveSkillBase> &liveskillbm;
//extern zDataBM<zSoulStoneB, SoulStoneBase> &soulstonebm;
//extern zDataBM<zHairStyleB, HairStyle> &hairstylebm;
//extern zDataBM<zHairColourB, HairColour> &haircolourbm;
//extern zDataBM<zCountryMaterialB, CountryMaterial> &countrymaterialbm;
//extern zDataBM<zHeadListB, HeadList> &headlistbm;
//extern zDataBM<zPetB, PetBase> &petbm;

#pragma pack(pop)

#endif 





