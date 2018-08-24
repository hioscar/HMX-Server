#ifndef __NET_SOCKET_H_
#define __NET_SOCKET_H_


#include "NetIOBuffer.h"

/*
 *
 *	Detail: Socket �� 
 *
 *  Created by hzd 2013-1-1
 *
 */
enum ERecvType
{
	REVC_FSRS_NULL = 0,
	REVC_FSRS_HEAD,
	REVC_FSRS_BODY,
};

class NetSocket : public tcp::socket
{
	friend class NetServer;
	friend class NetClient;
public:
	NetSocket(io_service& rIo_service);
	virtual ~NetSocket();

	// ���SocketID����0��ʼ���� 
	inline uint64_t SocketID() const { return m_usSocketID; }

	//  ѹ��Ҫ׼�����͵����� 
	void ParkMsg(const uint8_t* data, int32_t leng);

	/***
	 * ��ȡ�����е����� 
	 * -1 �����쳣
	 * 0 �ȴ���
	 * > 0���ݳ���
	 */ 
	int ReadDataMsg(uint8_t** data);

	// �Ƴ������е����� 
	void RemoveQueueHeader();

	// ����Socket�����Խ����շ����� 
	void Run();

	// ���Socket�ͻ���IP��ַ 
	const string GetIp() const;

	// ��������Ķ˿� 
	uint16_t GetPort() const;

	// ���ر�Socket(�����Ͽ��ͻ���) 
	void OnEventColse();

	 // �����Ͽ� 
	void SetTimeout(int32_t nTimeout);

	// ��ʱ���� 
	void TimeoutStart();

	//  ��ʱ�ر� 
	void TimeoutCancel();

	/*
	 *	�ж϶���Ϣ������Ϊwarriting 
	 */
	inline void BreakUpdateIO() { m_bBreakUpdateIo = true; }

	/*
	 *	ȥ���жϣ���read��Ϣ����waitting�� 
	 */
	inline void UnBreakUpdateIO() {m_bBreakUpdateIo = false; }

	/*
	 * �����¼�������ر�socket
	 */ 
	inline void SetLocalClose( bool bEventClose) { m_bEnventClose = bEventClose; }
	inline bool GetIsClose() const { return m_bEnventClose; }
	inline void SetIsCloseBeing(bool isBegin) { m_bEventCloseBegin = isBegin; }
	inline bool GetIsCloseBegin() const { return m_bEventCloseBegin; }
	inline void SetIsCloseFinish(bool isFinish) { m_bEventCloseFinish = isFinish; }
	inline bool GetIsCloseFinish() const { return m_bEventCloseFinish; }

private:

	NetSocket();

	// �Ͽ� socket
	void Disconnect();

	// �ر� socket
	void HandleClose(const boost::system::error_code& error);
	
	// �ָ������캯������״̬ 
	void Clear();

	// �յ�ָ���������ݻص����� 
	void RecvMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	//  �������ݻص����������ͺ����������ݣ����ѡ��������ͣ�һ�㲻�ᷢ�����������
	void SendMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	//  ����Ϣͷ 
	void ReadMsg(mutable_buffers_1& _buffers, uint32_t dataLen);

	// ��ʱ�ص�����������ر� socket 
	void HandleWait(const boost::system::error_code& error);

private:

	uint64_t			m_usSocketID;			// socketID�� һ���������� Socket ΨһID��0��ʼ 
	mutable_buffers_1	m_cRecvHeadBuffer;		// �յ�ͷ���ݻ������ 
	mutable_buffers_1	m_cRecvBodyBuffer;		// �յ�ͷ���ݻ������ 

	deadline_timer		m_cTimer;				// �շ���ʱ�������ڼ���û����û���������ͨ�ţ�������ɫ HandleWait ���� 
	deadline_timer		m_cCloseTimer;			// �ر����Ӷ�ʱ�� 

	// һ�����뷢���м�ת��(Buffer)�ռ�
	ERecvType			m_eRecvStage;
	char				m_arrRecvBuffer[PACKAGE_MAX_SIZE];

	DataBuffer*		recvQueueHeader_;	//����Ҫ���͵�ͷ
	DataBuffer*		recvQueueLastest_;	//��������Ľ�β

	int32_t				m_nTimeout;			// ��ʱ�Ͽ�,0��,>0ָ������ 

	bool m_bBreakUpdateIo; /* �ж��յ�IO������Ϣ���ڵȴ��� */ 

	bool m_bEnventClose;		// �Ƿ����˳��¼� 
	bool m_bEventCloseBegin;	// ��ʼ�˳��¼�
	bool m_bEventCloseFinish;	// ����˳��¼�

	boost::mutex   m_writeBufferMutex;
};

typedef boost::function<void(NetSocket& pSocket)>	PNetServerEnterHandler;
typedef boost::function<void(NetSocket& pSocket)>	PNetServerExistHandler;
typedef boost::function<void(NetSocket& pSocket, NetMsgSS* pMsg,int32_t nSize)>	PNetServerOnMsgHandler;


typedef list<NetSocket*> SocketList;
typedef list<NetSocket*>::iterator SocketListIter;
typedef vector<NetSocket*> SocketVector;
typedef vector<NetSocket*>::iterator SocketVectorIter;

typedef map<uint64_t,NetSocket*> SocketMap;
typedef map<uint64_t, NetSocket*>::iterator SocketMapIter;

#endif

