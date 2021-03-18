#include "joy.h"

MemCheck::MemCheck(){
	std::cout<< "construct\n";
}
MemCheck::~MemCheck(){
	std::cout << "release\n";
}

void MemCheck::ShowMsg(){
	std::cout << m_sMsg << std::endl;
}


void test_joy(void)
{
	std::cout << "this is joy module\n";
	std::cout << "sizeof string:" << sizeof(std::string) << std::endl;;
	std::vector<int*> vPtr;
	for (int i = 0; i < 10; ++i){
		int *pInt = new int(1);
		int numInt = 2;
		std::cout << "addr:"<< (void*)(pInt) << "\t" << &numInt << std::endl;
		//delete pInt;
		vPtr.push_back(pInt);
	}
	for(auto it : vPtr){
		delete it;
	}
	return;
}
