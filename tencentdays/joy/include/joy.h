#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <malloc.h>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstring>

/*
 * some feature test
 * */

thread_local uint32_t g_Count = 0;

class InsertObj{
	public:
		InsertObj(){}
		~InsertObj(){}
		std::string m_sStr1;
		std::string m_sStr2;
};

class ObjSize{
	public:
		ObjSize(){}
		~ObjSize(){}
		void SetNull()
		{
			if (m_pInsertobj)
			{
				delete m_pInsertobj;
			}
		}
		int m_int = 0;
		std::string m_sStr1;
		std::string m_sStr2;
		std::string m_sStr3;
		InsertObj  *m_pInsertobj;
};

class MemCheck{
	public:
		MemCheck();
		~MemCheck();
		std::string m_sMsg = "bbbbbbbbbdfjebfjhebsjhbfhjrbsAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		void ShowMsg();
};


void test_joy(void);

const int NUM_OF_MINHASH = 100*1000;

void testMem()
{
    std::vector<int*> vpMem;
    vpMem.reserve(NUM_OF_MINHASH);
    sleep(10);
	std::cout << "start alloc mem\n";
    for (int idx = 0; idx < NUM_OF_MINHASH; ++idx)
    {
        usleep(100);
        int *pTmp = new int[1000]{0};
        if (pTmp)
        {
            vpMem.push_back(pTmp);
        }
	if (idx %10000 == 0){std::cout << "alloc 10k, idx=" << idx <<std::endl; usleep(1000);}
    }
    std::cout << "start release mem\n";
    for (int idx = 0; idx < vpMem.size(); ++idx)
    {
        usleep(100);
        if (idx %10000 == 0)
		{
			std::cout << "release 10k, idx=" << idx <<std::endl; 
			usleep(1000);
			// release mem for system
			malloc_trim(0);
		}
        int * ppTmp = vpMem[idx];
        delete []ppTmp;
    }
}

class PtrEle{
	public:
	PtrEle(){std::cout << "PtrEle Construct\n"; }
	virtual ~PtrEle(){std::cout << "PtrEle Destory\n";}
	virtual void f(); 
};

class DPtrEle : public PtrEle{
	public:
	DPtrEle(){std::cout << "DPtrEle Construct\n";}
	virtual ~DPtrEle() {std::cout << "DPtrEle Destory\n";}
	virtual void f();
};

void test_ptr();

void test_epoll_server();

void test_epoll_client();
