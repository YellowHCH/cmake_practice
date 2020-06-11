#include "more_effective_c++.h"


// item 1

//item 2
class Item2{
public:
  void test_const_to_nonconst()
  {
    const int conInt = 0;
    int *pCI =(int *)(&conInt);
    //conInt = 1; // error
    *pCI = 1; // true, we can transfer conInt's pointer to nonconst
    //int *pCI2 = static_cast<int *>(&conInt); // false, c++ cast is type safe
    //*pCI2 = 2;
    int *pCI3 = const_cast<int *>(&conInt);
    *pCI3 = 3;
  }
};

///
#include <iostream>
void test_new()
{
  /*
  int *ptr[10];
  for(int i = 0; i < 10; ++i){
    ptr[i] = new int;
    *ptr[i] = i;
    
    std::cout << *ptr[i] << ", ";
  }
  std::cout << std::endl;
  for(int i = 0; i < 10; ++i)
  {
    delete ptr[i];
  }
  */
  int *ptr;
  ptr = new int[10];
  for(int i = 0; i < 10; ++i){
    ptr[i] = i;
    ;
    
    std::cout << ptr[i] << ", ";
  }
  std::cout << std::endl;
  delete ptr;
}
#include <list>
void test_stdcontainer_clear()
{
  std::cout << __func__ << std::endl;
  std::list<int *> m_list;
  int *val1 = new int(999);
  int *val2 = new int(666);
  m_list.push_back(std::move(val1));
  m_list.push_back(val2);
  m_list.clear();
  std::cout << " *val1 ==  " << *val1 <<std::endl;
}

/// size of long int
#include <string.h> // strlen
static const char pathname[] = "/home/qspace/data/goodseed/";
const char filename[] = "goodseed_9020061112.log";
void printTypeSize()
{
  std::cout << __func__ << std::endl;
  std::cout << "long int -- " << sizeof(long int) << std::endl;
  std::cout << "long long -- " <<sizeof(long long) << std::endl;
  std::cout << "double -- " << sizeof(double) << std::endl;
  std::cout << "int -- " << sizeof(int) << std::endl;
  std::cout << "size of str == " << sizeof(pathname) <<std::endl;
  std::cout << "strlen == " << strlen(pathname) << std::endl;
  char *file = const_cast<char*>(filename);
  file += 9;
  std::string strFile(file, 10);
  long int iTime = std::stol(strFile);
  std::cout << "strFile -> " <<strFile << std::endl;
  std::cout << "iTime -> " <<iTime << std::endl;
}

int main()
{
  //test_new();
  //test_stdcontainer_clear();
  printTypeSize();
  return 0;
}
