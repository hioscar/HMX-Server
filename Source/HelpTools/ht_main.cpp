#include <fstream>
#include <string>
#include <iostream>
#include "SrvEngine.h"
#include "DBConnection.h"
#include "LiuhecaiMgr.h"
#include "FileSystem.h"


// ��ȡ��������ŵ����ݿ���
int main(int argc, const char * argv[])
{

	//��ȡĿ¼��

	//���������
	CFileSystem statdir;

	//����Ҫ������Ŀ¼
	if (!statdir.SetInitDir("F:\\wwwroot\\liuhecai\\����"))
	{
		puts("Ŀ¼�����ڡ�");
		return 0;
	}

	//��ʼ����
	statdir.BeginBrowse("����*.*");
	printf("�ļ�����: %d\n��Ŀ¼����:%d\n", statdir.GetFileCount(), statdir.GetSubdirCount());

	//LiuhecaiMgr* liuMgr = new LiuhecaiMgr();
	//liuMgr->DoSomethings();
	return 0;
}



