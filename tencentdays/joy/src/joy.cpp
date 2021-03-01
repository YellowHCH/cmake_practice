#include "joy.h"

void test_joy(void)
{
	std::cout << "this is joy module\n";
	ObjSize * objsize = new ObjSize();
	std::cout << "#1 -- " << sizeof(*objsize) << std::endl;
	objsize->m_sStr1 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	objsize->m_sStr2 = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
	std::cout << "#2 -- " << sizeof(*objsize) << std::endl;
	objsize->m_pInsertobj = new InsertObj();
	objsize->SetNull();
	delete objsize;
}
