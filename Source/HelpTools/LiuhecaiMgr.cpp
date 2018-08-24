#include "LiuhecaiMgr.h"



LiuhecaiMgr::LiuhecaiMgr():m_pDbConn(NULL), m_nYear(0), m_nType(0)
{
	m_pXml = new zXMLParser();
}


LiuhecaiMgr::~LiuhecaiMgr()
{
}

void LiuhecaiMgr::DoSomethings()
{
	if (m_pDbConn == NULL)
	{
		if (!ConnectDb())
		{
			ASSERT(0);
			return;
		}
	}

	//Load(TYPE_OPEN, 2017, "F:\\wwwroot\\liuhecai\\����\\������¼\\2017��(����)������¼(��154��).txt");
	//Load(TYPE_OPEN, 2016, "F:\\wwwroot\\liuhecai\\����\\������¼\\2016��(����)������¼(��151��).txt");
	//Load(TYPE_OPEN, 2015, "F:\\wwwroot\\liuhecai\\����\\������¼\\2015��(����)������¼(��152��).txt");
	//Load(TYPE_OPEN, 2014, "F:\\wwwroot\\liuhecai\\����\\������¼\\2014��(����)������¼(��152��).txt");
	//Load(TYPE_OPEN, 2013, "F:\\wwwroot\\liuhecai\\����\\������¼\\2013��(����)������¼(��152��).txt");
	//Load(TYPE_OPEN, 2012, "F:\\wwwroot\\liuhecai\\����\\������¼\\2012��(����)������¼(��152��).txt");
	//Load(TYPE_OPEN, 2011, "F:\\wwwroot\\liuhecai\\����\\������¼\\2011��(����)������¼(��154��).txt");
	//Load(TYPE_OPEN, 2010, "F:\\wwwroot\\liuhecai\\����\\������¼\\2010��(����)������¼(��152��).txt");
	//Load(TYPE_TIANJISI, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\���ʫ.txt");
	//Load(TYPE_FUZUTIANSHU, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\��۷������.txt");
	//Load(TYPE_NAOJINJIZHUANWAN, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\�Խת��.txt");
	//Load(TYPE_TEMASHI, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\����ʫ.txt");
	Load(TYPE_BAIXIAOJIE, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\�׽������ȷ�ʫ.txt");
	Load(TYPE_BAIDAJIE, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\�ٴ�������Cʫ.txt");
	Load(TYPE_JINGZHUI7WEI, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\��׼��β.txt");
	Load(TYPE_ZENGSHIDONGWU, 2017, "F:\\wwwroot\\liuhecai\\����\\����ʫ\\��Ůʿ���ﶯ��.txt");
}

bool LiuhecaiMgr::ConnectDb()
{
	unsigned int readtimeout = 10;
	unsigned int writetimeout = 10;
	unsigned int conntimeout = 10;
	m_pDbConn = new db::DBConnection();
	m_pDbConn->setReadTimeout(readtimeout);
	m_pDbConn->setWriteTimeout(writetimeout);
	m_pDbConn->setConnectTimeout(conntimeout);
	bool ret = m_pDbConn->connect("127.0.0.1", "root", "123456", "liuhecai", 3306);
	return ret;
}

bool LiuhecaiMgr::Load(int32_t type,int32_t year, const char* cstrFileName)
{
	m_cFileStream.open(cstrFileName, std::ios::in);
	if (!m_cFileStream.is_open() ||
		m_cFileStream.fail() ||
		m_cFileStream.bad())
	{
		printf("[ERROR]:file open fail!\n");
		return false;
	}
	printf("���������ļ�:%s\n", cstrFileName);
	m_nYear = year;
	m_nType = type;
	NextRow();
	return true;
}

bool LiuhecaiMgr::NextRow()
{
	for (;;)
	{
		if (std::getline(m_cFileStream, m_strLine))
		{
			if (m_strLine.empty())
			{
				return false;
			}
			else
			{
				if (strlen(m_strLine.c_str()) == 0 || strcmp(m_strLine.c_str(), "\n") == 0 || strcmp(m_strLine.c_str(), "\t") == 0 || strcmp(m_strLine.c_str(), "\r") == 0)
				{
					return false;
				}
				AnalyseLine(m_strLine);
			}
			m_strLine.clear();
		}
		else
		{
			m_cFileStream.close();
			return false;
		}
	}

	return true;
}


void LiuhecaiMgr::AnalyseLine(const std::string& i_strLine)
{
	if (m_nType == TYPE_OPEN)
	{
		::liuhc::OpenInfo proto;
		if (m_nYear >= 2010 && m_nYear <= 2017)
		{
			AnalyseLine2010_2017(m_nYear, i_strLine, proto);
		}
		else if (m_nYear >= 2005 && m_nYear <= 2009)
		{
			AnalyseLine2005_2009(m_nYear, i_strLine, proto);
		}
		else
		{
			return;
		}

		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_open", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_TIANJISHI)
	{
		::liuhc::TianJiShiInfo proto;
		TianJiShi(i_strLine,proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_tianjishi", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_FUZUTIANSHU)
	{
		::liuhc::FuzutianshuInfo proto;
		HKfuzutianshu(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_fuzutianshu", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_NAOJINJIZHUANWAN)
	{
		::liuhc::NaojinjizhuanwanInfo proto;
		NaoJingJiZhuanWan(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_naojinjizhuanwan", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_TEMASHI)
	{
		::liuhc::TemashiInfo proto;
		Temashi(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_temashi", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_BAIXIAOJIE)
	{
		::liuhc::BaiXiaoJieInfo proto;
		BaiXiaoJieXianFeng(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_baixiaojie", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_BAIDAJIE)
	{
		::liuhc::BaiDaJieInfo proto;
		BaiDaJieBanJu(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_baidajie", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_JINGZHUI7WEI)
	{
		::liuhc::JingZhui7WeiInfo proto;
		JingZhui7Wei(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_jingzhui7wei", proto);
		if (ret == 0)
		{
			return;
		}
	}

	if (m_nType == TYPE_ZENGSHIDONGWU)
	{
		::liuhc::ZengshiChengYuDongWuInfo proto;
		ZhengShiChengYuDongWu(i_strLine, proto);
		int ret = doInsertProto(*m_pDbConn, "stb_caipiao_zengshichengyudongwu", proto);
		if (ret == 0)
		{
			return;
		}
	}
	

	//2004
	//2004��01��20��007��:05-32-28-31-09-06 ����:19(ţ)
	//2004��01��27��008��:40-41-13-18-10-29 ����:04(��)(2004��������)

	//2003
	//01��23�ձ�����007��36-06-38-27-14-23��49���ܷ�193���� 
	//01��28����������008��30-10-25-46-05-41��48���ܷ�205�����´���౦
	//04��15��������030��37-39-15-28-27-09��33���ܷ�188������ڽ�౦

	//2002
	//07��02��(��δ����)052��04-26-31-33-36-38��28�� �ܷ�196�� 
	//07��04��(���Ͻ���)053��05-32-34-38-39-49��08�� �ܷ�205��(��ʼ����48��49��)

	//2001
	//2001��01��02��(�ҳ����)001��13-20-35-38-44-45��05�� �ܷ�200��

	//2000
	//2000��10��17��092��:44-41-18-12-09-02��24�� �ܷ�:150��
}


void LiuhecaiMgr::AnalyseLine2010_2017(int32_t year, const std::string& i_strLine, ::liuhc::OpenInfo& proto)
{
	//2017 085��:36-04-06-27-47-49T03��/��/��
	//2016 151��:09-08-28-17-15-12T33��/��/��
	//2015 152��:22-24-11-25-02-12T03��/��/ˮ
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/.");
	if (vecD.size() >= 10)
	{
		proto.set_year(year);
		proto.set_date(0);
		proto.set_week(0);
		proto.set_qi(atoi(vecD[0].c_str()));
		proto.set_pm1(atoi(vecD[1].c_str()));
		proto.set_pm2(atoi(vecD[2].c_str()));
		proto.set_pm3(atoi(vecD[3].c_str()));
		proto.set_pm4(atoi(vecD[4].c_str()));
		proto.set_pm5(atoi(vecD[5].c_str()));
		proto.set_pm6(atoi(vecD[6].c_str()));
		proto.set_tema(atoi(vecD[7].c_str()));
		proto.set_tema_shangx((char*)m_pXml->charConv((BYTE*)(vecD[7].c_str() + 2), "GBK", "UTF-8"));
		proto.set_tema_bose((char*)m_pXml->charConv((BYTE*)vecD[8].c_str(), "GBK", "UTF-8"));
		proto.set_tema_wuxing((char*)m_pXml->charConv((BYTE*)vecD[9].c_str(), "GBK", "UTF-8"));

		if (proto.tema() % 2 == 1)
			proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"��", "GBK", "UTF-8"));
		else
			proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"˫", "GBK", "UTF-8"));
	}
	else
	{
		printf("��������:%s\n", i_strLine.c_str());
	}
}

void LiuhecaiMgr::AnalyseLine2005_2009(int32_t year, const std::string& i_strLine, ::liuhc::OpenInfo& proto)
{
	//2009
	//010��01��25������:44 40 47 04 12 19 ��49���̵���
	//011��01��27���ڶ�:42 13 07 21 17 45 ��36����˫ˮ ��Ф
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/ ");

	proto.set_year(2017);
	proto.set_date(0);
	proto.set_week(0);
	proto.set_qi(atoi(vecD[0].c_str()));
	proto.set_pm1(atoi(vecD[1].c_str()));
	proto.set_pm2(atoi(vecD[2].c_str()));
	proto.set_pm3(atoi(vecD[3].c_str()));
	proto.set_pm4(atoi(vecD[4].c_str()));
	proto.set_pm5(atoi(vecD[5].c_str()));
	proto.set_pm6(atoi(vecD[6].c_str()));
	proto.set_tema(atoi(vecD[7].c_str()));
	proto.set_tema_shangx((char*)m_pXml->charConv((BYTE*)(vecD[7].c_str() + 2), "GBK", "UTF-8"));
	proto.set_tema_bose((char*)m_pXml->charConv((BYTE*)vecD[8].c_str(), "GBK", "UTF-8"));
	proto.set_tema_wuxing((char*)m_pXml->charConv((BYTE*)vecD[9].c_str(), "GBK", "UTF-8"));

	if (proto.tema() % 2 == 1)
		proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"��", "GBK", "UTF-8"));
	else
		proto.set_tema_dans((char*)m_pXml->charConv((BYTE*)"˫", "GBK", "UTF-8"));

}

void LiuhecaiMgr::NaoJingJiZhuanWan(const std::string& i_strLine, ::liuhc::NaojinjizhuanwanInfo& proto)
{
	//2015���018��:����������������һ���˹����ࡣ�����˺�, ����Ů��ȴ�����������, Ϊʲô������ ? -- - �� : û�����İ���
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/ ");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 8));

		stringstream ss;
		if (vecD.size() >= 2)
			ss << vecD[1];
		if(vecD.size() >= 3)
			ss << vecD[2];
		if (vecD.size() >= 4)
			ss << vecD[3];

		proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::TianJiShi(const std::string& i_strLine, ::liuhc::TianJiShiInfo& proto)
{
	//��001��:���ɳ²�������,һ�嵥��������,��:��һ��׼ʱ����
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/ ");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::BaiXiaoJieXianFeng(const std::string& i_strLine, ::liuhc::BaiXiaoJieInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::BaiDaJieBanJu(const std::string& i_strLine, ::liuhc::BaiDaJieInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::HKfuzutianshu(const std::string& i_strLine, ::liuhc::FuzutianshuInfo& proto)
{
	//��112��:�������������, �������������(��������)
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::Temashi(const std::string& i_strLine, ::liuhc::TemashiInfo& proto)
{
	//��001��:��ƫ����,��ʵ���˵�; �������б�,С�۹����Ρ�
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::JingZhui7Wei(const std::string& i_strLine, ::liuhc::JingZhui7WeiInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}

void LiuhecaiMgr::ZhengShiChengYuDongWu(const std::string& i_strLine, ::liuhc::ZengshiChengYuDongWuInfo& proto)
{
	std::vector<std::string> vecD;
	stringtok(vecD, i_strLine, ":-T/");
	if (vecD.size() >= 2)
	{
		proto.set_year(m_nYear);
		proto.set_qi(atoi(vecD[0].c_str() + 2));
		if (vecD.size() == 2)
		{
			proto.set_text((char*)m_pXml->charConv((BYTE*)(vecD[1].c_str()), "GBK", "UTF-8"));
		}
		else
		{
			stringstream ss;
			ss << vecD[1];
			ss << vecD[2];
			proto.set_text((char*)m_pXml->charConv((BYTE*)(ss.str().c_str()), "GBK", "UTF-8"));
		}
	}
	else
	{
		ASSERT(0);
	}
}



