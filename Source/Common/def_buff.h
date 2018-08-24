#ifndef __DEF_BUFF_H_
#define __DEF_BUFF_H_

#include <vector>


#define MAX_BUFF_EFFECT_NUM 5

enum EffectAimType
{
	EFFECT_AIM_TYPE_FROM		= 1,	// ʩ���� 
	EFFECT_AIM_TYPE_TO			= 2,	// ��ʩ���� 
	EFFECT_AIM_TYPE_FROM_RANGE	= 3,	// ʩ���߷�Χ�� 
	EFFECT_AIM_TYPE_TO_RANGE	= 4,	// ��ʩ���߷�Χ�� 
};

enum EffectRangeType
{
	EFFECT_RANGE_TYPE_AROUND	= 1,	// ��Χ 
	EFFECT_RANGE_TYPE_Angle		= 2,	// �н� 
};

enum BuffEffectType
{
	BUFF_EFFECT_TYPE_NULL,

	BUFF_EFFECT_TYPE_SHOUJI				= 1,	// �ܻ� 
	BUFF_EFFECT_TYPE_JIDAO				= 2,	// ���� 
	BUFF_EFFECT_TYPE_FUKONG				= 3,	// ���� 
	BUFF_EFFECT_TYPE_JITUI				= 4,	// ���� 
	BUFF_EFFECT_TYPE_MIWU				= 5,	// ���� 
	BUFF_EFFECT_TYPE_CHENMO				= 6,	// ��Ĭ 
	BUFF_EFFECT_TYPE_DINGSHEN			= 7,    // ���� 
	BUFF_EFFECT_TYPE_HUNLUAN			= 8,    // ���� 
	BUFF_EFFECT_TYPE_XUANYUN			= 9,    // ѣ�� 
	BUFF_EFFECT_TYPE_LIUXIE				= 10,    // ��Ѫ 
	BUFF_EFFECT_TYPE_HUANMAN			= 11,    // ���� 
	BUFF_EFFECT_TYPE_XIYIN				= 12,    // ���� 
	BUFF_EFFECT_TYPE_KANGSHOUJI			= 13,    // ���ܻ� 
	BUFF_EFFECT_TYPE_KANGJIDAO			= 14,    // ������ 
	BUFF_EFFECT_TYPE_KANGFUKONG			= 15,    // ������ 
	BUFF_EFFECT_TYPE_KANGMIWU			= 16,    // ������ 
	BUFF_EFFECT_TYPE_KANGCHENMO			= 17,    // ����Ĭ 
	BUFF_EFFECT_TYPE_KANGDINGSHEN		= 18,    // ������ 
	BUFF_EFFECT_TYPE_KANGHUNLUAN		= 19,    // ������ 
	BUFF_EFFECT_TYPE_KANGXUANYUN		= 20,    // ��ѣ�� 
	BUFF_EFFECT_TYPE_KANGHUANMAN		= 21,    // ������ 
	BUFF_EFFECT_TYPE_KANGLIUXIE			= 22,    // ����Ѫ 
	BUFF_EFFECT_TYPE_BAOJILV			= 23,    // ������ 
	BUFF_EFFECT_TYPE_SHANBILV			= 24,    // ������ 
	BUFF_EFFECT_TYPE_GEDANGLV			= 25,    // ���� 
	BUFF_EFFECT_TYPE_MINGZHONGLV		= 26,    // ������ 
	BUFF_EFFECT_TYPE_BAOJIZHI			= 27,    // ����ֵ 
	BUFF_EFFECT_TYPE_GEDANGZHI			= 28,    // ��ֵ 
	BUFF_EFFECT_TYPE_WUGONG				= 29,    // �乥 
	BUFF_EFFECT_TYPE_NEIGONG			= 30,    // �ڹ� 
	BUFF_EFFECT_TYPE_SHENGMING			= 31,    // ���� 
	BUFF_EFFECT_TYPE_WUFANG				= 32,    // ��� 
	BUFF_EFFECT_TYPE_NEIFANG			= 33,    // �ڷ� 
	BUFF_EFFECT_TYPE_SHENGMINGXIUGUAI	= 34,    // �����޸� 
	BUFF_EFFECT_TYPE_DADUAN				= 35,    // ��� 

	BUFF_EFFECT_TYPE_KANGJITUI			= 36,    // ������ 
	BUFF_EFFECT_TYPE_MAX		 		// ������� 
};

enum BuffFlag
{
	BUFF_EFFECT_FLAG_MOMENTARY		= 0x00000001,	// ˲ʱ 
	BUFF_EFFECT_FLAG_REVERSIBLE		= 0x00000002,	// ���� 
	BUFF_EFFECT_FLAG_STACKABLE		= 0x00000004,	// �ɵ��� 
	BUFF_EFFECT_FLAG_REPLACEABLE	= 0x00000008,	// ����� 
	BUFF_EFFECT_FLAG_INTERRUPTIBLE	= 0x00000010,	// �ɴ�� 
	BUFF_EFFECT_FLAG_SAVABLE		= 0x00000020,	// ��Ҫ���� 
};

class SceneNpc;
typedef void(*BuffEffectFunc)(SceneNpc* /* ʩ���� */, SceneNpc* /* ��ʩ���� */, EffectAimType/* Ŀ������ */, EffectRangeType/* ��Χ���� */,
	int32_t/* ���� */, int32_t/* ���� */, float32/* �Ƕ�cosֵ */,int32_t nEffectNum/* ���Ӱ������ */);

struct BuffEffect
{
	BuffEffectType		eType;					// Ч������ 
	//int32				nType;
	int32_t				nLimitFlag;				// Ч������ʹ�ñ��(BuffFlag������λ����ֵ) 
	BuffEffectFunc		pCallBack;				// Ч������ 
};

struct BuffData
{
	int32_t		nBuffID;						// BuffID 
	int32_t		nLimitFlag;						// ʹ�ñ�� 
	int32_t		nLifeTime;						// ��������(��λ:����) 
	int32_t		nEffectNum;						// ���򵽵������� 
	struct Effect
	{
		BuffEffectType		nEffectID;			// Ч��ID 
		int32_t				nProbability;		// ���ָ���(0Ϊһ������) 
		EffectAimType		eAimType;			// ���ö������� 
		EffectRangeType		eRangeType;			// ���÷�Χ���� 
		int32_t				nDist;				// ���� 
		float32				fCosAngle;			// �Ƕ�(cosֵ) 
		int32_t				nParam;				// ����ֵ 
		int32_t				nTimePoint;			// Ч����Чʱ���(��λ:����) 
	}	arrEffect[MAX_BUFF_EFFECT_NUM];
};

struct DamageReduce
{
	int32_t player_num;
	int32_t reduce_param;
};

#endif


