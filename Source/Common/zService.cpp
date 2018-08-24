/**
 * \brief ʵ�ַ����������
 *
 * 
 */
#include "SrvEngine.h"


/**
 * \brief CTRL + C���źŵĴ�����,��������
 *
 * \param signum �źű��
 */
static void ctrlcHandler(int signum)
{
  H::logger->info("ctrlcHandler");
  fprintf(stderr,"ctrlcHandler\n");
  //���û�г�ʼ��zServiceʵ��,��ʾ����
  zService *instance = zService::getInst();
  instance->Terminate();
}

/**
 * \brief HUP�źŴ�����
 *
 * \param signum �źű��
 */
static void hupHandler(int signum)
{
  H::logger->info("hupHandler");
  //���û�г�ʼ��zServiceʵ��,��ʾ����
  zService *instance = zService::getInst();
  instance->reloadConfig();
}

zService *zService::inst = NULL;

/**
 * \brief ��������ܵ�������
 */
void zService::main()
{
  H::logger->debug("zService::main");
  //��ʼ������,��ȷ�Ϸ����������ɹ�
  if(signal(SIGTERM  , ctrlcHandler)==SIG_ERR)
  {
	fprintf(stderr,"�ź�����ʧ��\n");
  }

  srand((unsigned)time(NULL));

  if (init()
  && validate())
  {
    //�������ص��߳�
    while(!isTerminate())
    {
      if (!run())
      {
        break;
      }
    }
  }

  //��������,�ͷ���Ӧ����Դ
  finaly();
}

