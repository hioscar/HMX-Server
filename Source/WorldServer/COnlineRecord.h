#ifndef __CONLINE_RECORD_H_
#define __CONLINE_RECORD_H_

#include "SrvEngine.h"
#include "maj/server_log.pb.h"
#include "Global.hpp"


class COnlineRecord : public Single<COnlineRecord>
{
public:
	COnlineRecord();
	~COnlineRecord();

	void Init();

	void doRecord();

private:
	
	fogs::FogsTimer* m_pSaveDataTimer;

	uint32_t m_online_num;	// ��������
	uint32_t m_inroom_num;	// ��ǰ�ڷ�������

	uint32_t m_last_online_num;
	uint32_t m_last_inroom_num;

};


#endif



