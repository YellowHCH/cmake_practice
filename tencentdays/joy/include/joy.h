#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <malloc.h>

/*
 * some feature test
 * */

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
			malloc_trim(0);
		}
        int * ppTmp = vpMem[idx];
        delete []ppTmp;
    }
}
