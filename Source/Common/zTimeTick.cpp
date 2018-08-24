/**
* \brief zTimeTick��ʵ���ļ�
*/
#include "SrvEngine.h"


zTimeTick::zTimeTick():epochStd(boost::gregorian::date(1970, Jan, 1)/*,time_duration(0, 0, 0)*/),beijingDuration(8, 0, 0)
{

}

zTimeTick::~zTimeTick()
{

}

void zTimeTick::update()
{
	if (!nowtime)
	{
		nowtime = NowTime();
		checkHourUnit();
		return;
	}
	else
	{
		nowtime = NowTime();
	}
	
	if (nowtime % 3600 == 0)
	{
		checkHourUnit();
	}
}

void zTimeTick::checkHourUnit()
{

}
