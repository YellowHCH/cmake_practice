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



int main()
{
  test_new();
  return 0;
}
