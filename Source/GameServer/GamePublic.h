#ifndef		___DEF_H_DDZ_PUBLIC_H_DEF__
#define		___DEF_H_DDZ_PUBLIC_H_DEF__
#include "CommonDef.h"
//���������������������С����
#define  __MJ_PLAYER_MAX_NUM__	(5)
#define  __MJ_PLAYER_MIN_NUM__	(2)
#define __MAJING_NUM__	(136)
#define __13_YAO_NUM__	(13)
#define __HUA_NUM_4__	(4)
#define __HUA_NUM_8__	(8)

//ÿ�˷����齫����
#define  __MJ_NUM__	(4)
//�������ܵ����� �������򿸵���
#define  __MJ_TOTAL_NUM__	(5)

//�ͻ�����,����˲��ù� ��������
#define __MAX_ROOM_NUM__	(6)

//����Ӯ��������
#define  _MJ_FANSHU_JIAOBEI_	(1)	//Ʈ
#define  _MJ_FANSHU_TIANHU_		(2)	//���
#define  _MJ_FANSHU_DIHU_		(2)	//�غ�
#define  _MJ_FANSHU_HAIDILAO_	(2)	//������
#define  _MJ_FANSHU_HAAO_	(2)	//������
#define  _MJ_FANSHU_DUIHUA_		(1)	//�Ի�
#define  _MJ_FANSHU_QINGYISHE_	(2)	//��һɫ
#define  _MJ_FANSHU_ANGONG_		(2) //����
#define  _MJ_FANSHU_GONG_		(1) //��ͷ���͵㿸����һ��
#define  _MJ_FANSHU_MINGTING_	(2)	//����
#define  _MJ_FANSHU_ANTING_		(1)	//��
#define  _MJ_FANSHU_DUIDUIHU_	(1)	//�ԶԺ�
#define  _MJ_FANSHU_DAIYAO_		(1)	//���ۺ�
#define  _MJ_FANSHU_KAWUXING_	(1)	//������
#define  _MJ_FANSHU_JIANGDUI_	(1)	//����
#define  _MJ_FANSHU_CHAJIAO_	(4)	//���
#define  _MJ_FANSHU_JUAZHU_		(4)	//����
#define  _MJ_FANSHU_ZHIMO_		(1)	//����
#define  _MJ_FANSHU_QIDUI_		(2)	//�߶�
#define  _MJ_FANSHU_MINGSIGUI_	(1)	//���Ĺ�
#define  _MJ_FANSHU_ANSIGUI_	(2)	//���Ĺ�
#define  _MJ_FANSHU_LONGQIDUI_	(3)	//���߶�
#define  _MJ_FANSHU_SHUANGLONGQIDUI_	(4)	//˫���߶�
#define  _MJ_FANSHU_DASANYUAN_	(3)	//����Ԫ
#define  _MJ_FANSHU_XIAOSANYUAN_		(2)	//С��Ԫ
#define  _MJ_FANSHU_SHOUZHUAYI_	(2)	//��ץһ
#define _MJ_FANSHU_DANDIAO_	    (1)
#define _MJ_FANSHU_HUNYISE_	    (1)	//��һɫ

//��Ϣ����
//������Ϸ�����ͷ����ͻ��˵���Ϣ��MainID: MSG_MDM_CGS_GAME   SUBID: SUB_GAME_CGS_GAME_MSG
//�յ���Ϸ��Ϣ�Ժ�Ҫ���½�����ʲô��Ϣ ת��Ϊ CMD_GF_GameFrameHead

//��Ϸ��ʼ������Ϣ
#define		_MJ_MSG_GAME_START_		(1)

//֪ͨ�����û��ӱ���  ��ҷ����Ƿ�ӱ�
#define		_MJ_MSG_PLAYER_JIABEI_		(2)

//�㲥�����û�ѡ��ӱ���Ϣ���
#define		_MJ_MSG_PLAYER_JIABEI_RET_	(3)

//�㲥�û�������Ϣ
#define		_MJ_MSG_PLAYER_HUANPAI_	(4)

//�㲥�û�ʹ�õ��߻��ƽ����Ϣ
#define		_MJ_MSG_PLAYER_HUANPAI_RET_	(5)

//��ҷ��ʹ��Ƹ������� ���������ʹ��Ƹ����
#define		_MJ_MSG_PLAYER_DAPAI_	(6)

//ָ֪ͨ���û����������Ƶ�
#define		_MJ_MSG_PLAYER_YAOPAI_	(7)

//ָ֪ͨ���û��������Ƶ�
#define		_MJ_MSG_PLAYER_YAOPAI_RET_	(8)


//�㲥�û�������
#define _MJ_MSG_PLAYER_PGH_	(9)

//ָ֪ͨ���û�������
#define		_MJ_MSG_PLAYER_HUPAI_		(10)


//�����û�ץ��  �㲥
#define		_MJ_MSG_PLAYER_ZHUAPAI_	(11)
//�㲥����
#define _MJ_MSG_GAME_HUANGPAI_	(12)

//���͸������/������Ϣ
#define 	_MJ_MSG_GAME_TING_	(13)
//��ҳ�����Ϣ
#define		_MJ_MSG_PLAYER_CHUAPAI_	(14)

//���������Ϣ ���߻���
#define		_MJ_MSG_PLAYER_TINGPAI_		(15)
#define		_MJ_MSG_PLAYER_TINGPAI_RET_	(16)
#define __MAX_HUPAI_NUM__	(9)//��������


//������������ߵ���ʾ
#define		_MJ_MSG_HU_PROMPT_	(17)


//�ͻ��˷��ʹ���Ĵ�����Ϣ����  ���������Ʒ��͸���ǰ�ͻ���
#define	_MJ_MSG_PLAYER_SEND_ERROR_PAI_	(18)


//������Ϣ
#define	_MJ_MSG_GAME_JIESHUAN_	(19)

//��Ϸ����
#define		_MJ_MSG_PLAYER_GAME_END_	(50)


//�û����ߴ���  ������Ӧ���������ݸ��û�
#define _MJ_GAME_RECONNECT_SCENE_		(51)



//��������
enum
{
	_MJ_TYPE_NULL_,		//���÷���
	_MJ_TYPE_RAND_ = 1,	//�������
};

//��������Ƶ�����
typedef enum
{
	_MJ_PAI_TYPE_NULL_ = 0x00,
	_MJ_PAI_TYPE_HUAZHU_ ,	//����
	_MJ_PAI_TYPE_NOTING_,		//û��
	_MJ_PAI_TYPE_TING_,		//����
}MJ_PAI_TYPE;
//�û�Ҫ������  ������ֻ�������ͺ�(������)
//�ͻ���Ҫ��ֻ����һ�����
//_MJ_YP_NORMAL_������������־�û��Ƿ�Ҫ��
typedef enum
{
	_MJ_YP_GUO_ = 0,//����Ҫ��
	_MJ_YP_PENG_,	//��
	_MJ_YP_GONG_,	//��
	_MJ_YP_HU_,		//��
	_MJ_YP_NORMAL_,		//��������
}MJ_USR_YP_TYPE;

//��������
typedef enum
{
	_MJ_USR_ACTION_NULL_ = 0x00,	//����Ϊ
	_MJ_USR_ACTION_ANGONG_ = 0x01,	//���� �Լ�ץ������
	_MJ_USR_ACTION_DIANGONG_ = 0x02,	//�㿸
	_MJ_USR_ACTION_HTGONG_ = 0x04,		//��ͷ��
	_MJ_USR_ACTION_PENG_ = 0x08,	//��
	_MJ_USR_ACTION_CHI_ = 0x10,	//��  ��ʱû��
}MJ_USR_ACTION;

//�Ƶ����� int 4�ֽ��ܱ�ʾ32�ֺ���
typedef enum
{
	_MJ_WIN_NULL_ = 0x0000,
	_MJ_WIN_TIANHU_ = 0x0001,		//���
	_MJ_WIN_DIHU_ = 0x0002,		//�غ�
	_MJ_WIN_HAIDILAO_ = 0x0004,	//������
	_MJ_WIN_QINGYISHE_ = 0x0008,	//��һɫ  ----
	_MJ_WIN_GONGHUA_ = 0x0010,		//���ϻ�
	_MJ_WIN_ZHIMO_ = 0x0020,		//����  -----
	_MJ_WIN_MINGTING_ = 0x0040,	//������
	_MJ_WIN_ANTING_ = 0x0080,		//������
	_MJ_WIN_DUIDUIHU_ = 0x0100,	//�ԶԺ�   ------
	_MJ_WIN_DAIYAO_ = 0x0200,		//����  ------  
	_MJ_WIN_KAWUXING_ = 0x0400,	//������   -----
	_MJ_WIN_JIANGDUI_ = 0x0800,	//����     -----
	_MJ_WIN_QIANGGANG_ = 0x1000,	//������
	_MJ_WIN_DUANYJ_ = 0x2000,	//��19
	_MJ_WIN_GONGPAO_ = 0x4000,	//������
	_MJ_WIN_HAAO_ = 0x8000,	//������
	_MJ_WIN_GONG_ 	 = 0x010000,	//��
	_MJ_WIN_DANDIAO_ 	 = 0x020000,	//����
	_MJ_WIN_PINGHU_ = 0x040000,	//��  ֻ�Ǻ��ı�־  �������Ͳ������ϼ���
	_MJ_WIN_QIDUI_ = 0x080000,	//�߶�
	_MJ_WIN_MINGSIGUI_ = 0x100000,	//���Ĺ�
	_MJ_WIN_ANSIGUI_ = 0x200000,	//���Ĺ�
	_MJ_WIN_SHOUZHUAYI_ = 0x400000,	//��ץ1
	_MJ_WIN_LONGQIDUI_  = 0x800000,	//���߶�
	_MJ_WIN_SHUANGLONGQIDUI_ = 0x1000000,	//˫���߶�
	_MJ_WIN_DASANYUAN_ = 0x2000000,	//����Ԫ
	_MJ_WIN_XIAOSANYUAN_ = 0x4000000,	//С��Ԫ
	_MJ_WIN_HUNYISE_ = 0x8000000,	//��һɫ

}MJ_WIN_TYPE;


//���ڵ�����
typedef enum
{
	_MJ_LOSE_FANGPAO_ = 0x01,	//�������Ʒ���
	_MJ_LOSE_GONG_,			//������Ʒ��ڻ�����
	_MJ_LOSE_ZIMO_,			//����
}MJ_LOSE_TYPE;

typedef enum
{
	_MJ_TING_NULL_	=	0,
	_MJ_TING_MINGTING_	,
	_MJ_TING_TING_,
}MJ_TING_TYPE;


//��Ϸ״̬ �������û�״̬���
typedef enum
{
	_MJ_PLAY_STATUS_FREE_ = 0,
	_MJ_PLAY_STATUS_JIABEI_,	//�ӱ�
	_MJ_PLAY_STATUS_FAPAI_,	//��Ϸ��ʼʱ����
	_MJ_PLAY_STATUS_BANK_,	//ѡ��ׯ��
	_MJ_PLAY_STATUS_HUANPAI_,	//ʹ�õ���
	_MJ_PLAY_STATUS_DAPAI_,		//����״̬
	_MJ_PLAY_STATUS_YAOPAI_,	//���Ƹ��û�������/��/����Ϣ���û�
	_MJ_PLAY_STATUS_HUPAI_,		//�û�����
	_MJ_PLAY_STATUS_HUANGPAI_,	//����
	_MJ_PLAY_STATUS_HU_JIESHUAN_,	//�����ƵĽ������
	_MJ_PLAY_STATUS_PLAYER_END_		//���״̬�� �����ƺ��������ϵ�״̬
}MJ_PLAY_STATUS;


//��������
typedef enum
{
	_MJ_CHUPAI_NULL_ = 0,	//��ͨ����
	_MJ_CHUPAI_MINGGONG_,	//��
	_MJ_CHUPAI_GONG_CHUPAI_,	//�������
	_MJ_CHUPAI_GONG_,	//����״̬(����/�㿸)
}MJ_CHUPAI_TYPE;


//��ҽ�������ṹ��
struct PLAYER_JIESUAN_DATA_STRUCT
{
	int32_t hutype;		//��������
	uint8_t fanshu;	//��Ӯ����
	uint8_t chirdid;	//˭����  ���������Ϊ��0
	uint8_t duihuanum;	//�Ի�����
	uint8_t bExist;		//�ͻ�������
	int32_t fpgold;		//���ڽ����
	int32_t ggold;		//���Ľ����
	int32_t hugold;		//���ƵĽ�������û�к����ǲ��ƽ����
	int32_t totalgold;	//�ܵ���Ӯ���
};

//����Ͳ����Ϣ
#define _CHAPAI_NUM_	(10)
struct PLAYER_CHAPAI_DATA_STRUCT
{
	uint8_t type;			//����  1:���� 2: ��� 0����
	uint8_t wchaired;		//Ӯ�����Ӻ�
	uint8_t lchaired;		//������Ӻ�
	uint8_t res;			//����
	int32_t goldnum;		//��Ӯ���
};

//���巢�ƹ���
typedef enum
{
	SCRT_RAND,	//�����
	SCRT_MANY,	//�����ƶ�Ͷ෢�������
	SCRT_LESS,	//�������پͶ෢�������
}SEND_CARD_RULE_TYPE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*		13����Ϣ�ṹ����			*/
//���������������������С����

#define  __MJ_PLAYER_MAX_NUM13__	(3)
#define  __MJ_PLAYER_MIN_NUM13__	(3)

#define __MAJING_NUM13__	(84)

//ÿ�˷����齫����
#define  __MJ_NUM13__	(13)
//�������ܵ����� �������򿸵���
#define  __MJ_TOTAL_NUM13__	(14)

#define  __MAX_OUTPAI_NUM13__ (16)

//��Ϣ����
//������Ϸ�����ͷ����ͻ��˵���Ϣ��MainID: MSG_MDM_CGS_GAME   SUBID: SUB_GAME_CGS_GAME_MSG
//�յ���Ϸ��Ϣ�Ժ�Ҫ���½�����ʲô��Ϣ ת��Ϊ CMD_GF_GameFrameHead

//��Ϸ��ʼ������Ϣ
#define		_MJ_MSG_GAME_START13_		(131)

//֪ͨ�����û��ӱ���  ��ҷ����Ƿ�ӱ�
#define		_MJ_MSG_PLAYER_JIABEI13_		(132)

//�㲥�����û�ѡ��ӱ���Ϣ���
#define		_MJ_MSG_GAME_START_RET13_	(133)

//�㲥�û�������Ϣ
#define		_MJ_MSG_PLAYER_HUANPAI13_	(134)

//�㲥�û�ʹ�õ��߻��ƽ����Ϣ
#define		_MJ_MSG_PLAYER_HUANPAI13_RET13_	(135)

//��ҷ��ʹ��Ƹ������� ���������ʹ��Ƹ����
#define		_MJ_MSG_PLAYER_DAPAI13_	(136)

//ָ֪ͨ���û����������Ƶ�
#define		_MJ_MSG_PLAYER_YAOPAI13_	(137)

//ָ֪ͨ���û��������Ƶ�
#define		_MJ_MSG_PLAYER_YAOPAI13_RET13_	(138)


//�㲥�û�������
#define _MJ_MSG_PLAYER_PGH13_	(139)

//ָ֪ͨ���û�������
#define		_MJ_MSG_PLAYER_HUPAI13_		(1310)


//�����û�ץ��  �㲥
#define		_MJ_MSG_PLAYER_ZHUAPAI13_	(1311)
//�㲥����
#define _MJ_MSG_GAME_HUANGPAI13_	(1312)

//���͸������/������Ϣ
#define 	_MJ_MSG_GAME_TING13_	(1313)
//��ҳ�����Ϣ
#define		_MJ_MSG_PLAYER_CHUAPAI13_	(1314)

//���������Ϣ ���߻���
#define		_MJ_MSG_PLAYER_TINGPAI13_		(1315)
#define		_MJ_MSG_PLAYER_TINGPAI13_RET13_	(1316)
//������������ߵ���ʾ
#define		_MJ_MSG_HU_PROMPT13_	(1317)


//�ͻ��˷��ʹ���Ĵ�����Ϣ����  ���������Ʒ��͸���ǰ�ͻ���
#define	_MJ_MSG_PLAYER_SEND_ERROR_PAI13_	(1318)


//������Ϣ
#define	_MJ_MSG_GAME_JIESHUAN13_	(1319)

//��Ϸ����
#define		_MJ_MSG_PLAYER_GAME_END13_	(1350)


//�û����ߴ���  ������Ӧ���������ݸ��û�
#define _MJ_GAME_RECONNECT_SCENE13_		(1351)

//S->C	//�㲥������ҿ��Ժ�����
//#define		_MJ_MSG_BROADCAST_TINGDATA13_		(1352)

#endif
