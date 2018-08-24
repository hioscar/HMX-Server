#ifndef __Net_SERVER_H_
#define __Net_SERVER_H_

#include "NetSocket.h"

#define MAX_SOCKETS 65536

/*-------------------------------------------------------------------
* @Brief : Socket��������װ��
*
* @Author:hzd 2012/04/03
*------------------------------------------------------------------*/
class NetServer : public io_service
{
public:

	/*
	 *
	 *	Detail: �����·�����
	 *  @param ���������
	 *  @param ����յ�������С
	 *  @param ���һ�η��ʹ�С(1+��)
	 *  @param �����ջ����С
	 *  @param ����ͻ����С
	 *  Created by hzd 2012/04/03
	 *
	 */
	NetServer(int32_t nMaxConnected);
	virtual ~NetServer();

	// ��ñ�ʶID
	int32_t SocketID();

	// �����������ַ������˿�
	void SetAddress(const char* pIp, uint16_t pPort);

	// ��ʱ�Ͽ�ʱ��(��)
	void SetTimeout(int32_t nTimeout);

	// ����Socket�¼��ص�(���û��ָ����������Ĭ�ϻص�������ʹ�ü̳л�ûص�)
	void SetHandler(PNetServerEnterHandler pEnter, PNetServerOnMsgHandler pMsg, PNetServerExistHandler pExit);

	// ��������
	void Start();

	// ֹͣ����
	void Stop();

	// ��Socket�������¹���
	void SetAccept(NetSocket& pSocket);

	// ��Ϣ����
	void OnUpdate();

	// ���Socket
	NetSocket& GetSocket(int32_t nIndex);

	// �Ѿ�������Socket����
	size_t ConnectedSockets();

	// �ڽ��н��ܵ�Socket����
	size_t AcceptingSockets();

	// ����������ӵ�socket
	NetSocket* getAcceptSocket(int64_t socketid);

	//  �������ʹ�õ�socket
	NetSocket* getUsedSocket(int64_t socketid);

	// ������ڵȴ����ӵ�socket 
	SocketMap&	getSetAccepts() { return m_setWaitAccept; }

	inline std::vector<NetSocket*>& GetNetSockets() { return m_vecSocket; }

private:

	//  IOѭ������
	void Run();

	// �����пͻ��������¼�������
	void HandleStart();

	//  ���ӻص�
	void HandleAccept(const boost::system::error_code& error, NetSocket* socket);

	// �����������
	void OnUpdateAccept();

	// ��������ϢSocket
	void OnUpdateRecived();

private:

	int32_t			m_nMaxConnected;			// ���Socket������ < 65536 
	int32_t			m_nServerID;				// ��������ʶΨһID  

	SocketMap		m_setWaitAccept;			// �������ӵ�socket
	SocketMap		m_mapHadAccepted;			// �����е�Socket  
	SocketMap		m_mapIsUsing;				// ʹ���е�Socket  
	
	std::vector<NetSocket*>	m_vecSocket;	// ���е�Scoket 

	tcp::endpoint   m_cServerAddr;				// �����ַ�� 
	tcp::acceptor   m_cAcceptor;				// ���ӹ����� 

	PNetServerEnterHandler		m_pOnEnter;		// ���ӻص� 
	PNetServerOnMsgHandler		m_pOnMsg;		// ��Ϣ�ص� 
	PNetServerExistHandler		m_pOnExit;		// �Ͽ��ص� 

	boost::thread  m_cServiceThread;
	boost::mutex   m_cClientListMutex;

};


#endif





