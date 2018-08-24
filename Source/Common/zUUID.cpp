#include "SrvEngine.h"
#ifdef __GNUC__
#include<sys/time.h>
#include<stdio.h>
#define EPOCHFILETIME 11644473600000000ULL 
#else
#include<windows.h>
#include<time.h>
#define EPOCHFILETIME 11644473600000000Ui64
#endif

uint64_t zUUID::get_time() {
#ifdef __GNUC__
	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint64_t time = tv.tv_usec;
	time /= 1000;
	time += (tv.tv_sec * 1000);
	return time;
#else
	FILETIME filetime;
	uint64_t time = 0;
	GetSystemTimeAsFileTime(&filetime);

	time |= filetime.dwHighDateTime;
	time <<= 32;
	time |= filetime.dwLowDateTime;

	time /= 10;
	time -= EPOCHFILETIME;
	return time / 1000;
#endif
}


zUUID::zUUID()
{
	epoch_ = 0;
	time_ = 0;
	machine_ = 0;
	sequence_ = 0;
}

zUUID::~zUUID() {

}


void zUUID::set_epoch(uint64_t epoch) {
	epoch_ = epoch;
}


void zUUID::set_machine(int32_t machine) {
	machine_ = machine;
}


uint64_t zUUID::generate() {
	int64_t value = 0;
	uint64_t time = get_time() - epoch_;

	//������41λʱ��
	value = time << 22;

	//�м�ʮλ�ǻ������� 

	value |= (machine_ & 0x3FF) << 12;

	//���12λ��squenceID
	value |= sequence_++ & 0xFFF;

	if (sequence_ == 0x1000) {
		sequence_ = 0;
	}
	return value;
}

uint32_t zUUID::generate32()
{
	uint64_t swtVal = 0x00000000ffffffff;
	uint64_t srcTime = get_time() - epoch_;
	uint32_t time = (uint32_t)(swtVal & srcTime);
	uint32_t machine = (uint32_t)(swtVal & machine_);
	//������21λʱ��
	uint32_t value = time << 11;
	//�м�5λ�ǻ������� 
	value |= (machine & 0x27F) << 6;
	//���6λ��squenceID
	value |= sequence_++ & 0x27F;
	if (sequence_ == 0x0100) {
		sequence_ = 0;
	}
	return value;
}

/*


#define __TEST__
#ifdef __TEST__
#include<iostream>
void test() {
	utils::unique_id_t * u_id_ptr = new utils::unique_id_t();
	u_id_ptr->set_epoch(uint64_t(1367505795100));
	u_id_ptr->set_machine(int32_t(100));
	for (int i = 0; i < 1024; ++i) {
		std::cout << u_id_ptr->generate() << std::endl;
	}

}
#endif

*/


//int 
//main(int argc, const char *argv[])
//{
//    test();
//    return 0;
//}
