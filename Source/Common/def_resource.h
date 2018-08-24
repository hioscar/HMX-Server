#ifndef __DEF_RESOURCE_H_
#define __DEF_RESOURCE_H_




#pragma pack(push, 1)

struct StRoleTypeInitCfg
{
	int32_t nRoleType;
	int32_t arrSkillId[5];
	int32_t nLandMapId;
	int32_t nLandX;
	int32_t nLandY;
	int32_t nInViewRange;
	int32_t nOutViewRange;
	int32_t nInitRed;
	int32_t nInitBlue;
	int32_t nAttackType;
	int32_t nSpeed;
};


struct StCharacterLevelCfg
{
	int32_t nIdx;			// ID  
	int32_t nCharType;	// ��ɫ����   
	int32_t nLevel;		// �ȼ� 
	int32_t nUpLevelExp;  // ��һ����Ҫ����  
	int32_t nRedMax;		// ����  
	int32_t nRedRecover;  // ��ظ�/s  
	int32_t nBlueMax;     // ����� 
	int32_t nBlueRecover; // ���ظ�/s 
	int32_t nPhysicAttack;// ��ͨ����  
	int32_t nPhysicDefend;// ��ͨ���� 
	int32_t nSpellAttack; // ���ܹ��� 
	int32_t nSpellDefend; // ���ܷ��� 
	int32_t nBaojilv;		// ������ 
	int32_t nBaoji;		// ����(����) 
	int32_t nGedanglv;    // ���ʣ��񵲶Է������˺��� 
	int32_t nGedang;		// ��ֵ 
	int32_t nShanbilv;	// ������(���ܶԷ��ļ���) 
	int32_t nMingZhonglv; // ������(���жԷ����ü���) 
};

// ��ͼ��Ϣ 
struct StMapInfoResCfg
{
	int32_t	nMapId;
	int32_t	nSceneType;
	std::string	strZoneFileName;
	std::string	strSceneFileName;
};

// ��ͼ���� 
struct StMapZoneResCfg
{
	int32_t nMapId;									// ��ͼID 
	int32_t nXAmount;									// ��������� 
	int32_t nYAmount;									// ���¸����� 
	int32_t nXCellLength;								// ����С�����赲��С���ӵ�λ��ͬ 
	int32_t nYCellLength;								// ���С�����赲��С���ӵ�λ��ͬ 
	int32_t nBlock;									// ������������ã� 
	int32_t nNpc;										// NPC���ã������ã� 
	std::string strData;							// 0246ֵ 
	std::vector<std::vector<int8_t> > regionValue;	// ������ӵ�ֵ 
};

// ��ͼ�赲 
struct StMapSceneResCfg
{
	int32_t nMapId;	// ��ͼID 
	int32_t nXAmount; // ��������� 
	int32_t nYAmount;	// ���¸����� 
	int32_t nXCellLength;// �����أ���С�ĸ��ӳ��� 
	int32_t nYCellLength;// �����أ���С�ĸ��ӳ��� 
	std::string strData; // 0246 ֵ 
	std::vector<std::vector<int8_t> > regionValue;	// ������ӵ�ֵ 
	/*--------------------------------------------
	 *  @brief    :	���صĴ�СҪ����ʵ��ͼ�ĳߴ���һ������
	 *  @input	  : ��ͼ����Ϊ(�׻�cm��)
	 *  @return   :	
	 *-------------------------------------------*/
};


// �������ñ� 
struct StQuestInfoResCfg  
{
	int32_t nId;
	int32_t nType;
	int32_t nSubType;

	std::string strTitle;
	std::string strContent;

	struct AcceptInfo
	{
		int32_t nType;
		int32_t nArg0;
		int32_t nArg1;

	};
	AcceptInfo accept[4];

	struct FinishInfo
	{
		int32_t nType;
		int32_t nArg0;
		int32_t nArg1;
	};

	FinishInfo finish[4];

	struct AwardInfo
	{
		int32_t nType;
		int32_t nArg0;
		int32_t nArg1;
	};

	AwardInfo award[4];

};

#pragma pack(pop)

#endif

