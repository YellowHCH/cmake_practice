#pragma once

#include <iostream>

/// bitset
#include <bitset>
#include <time.h>
#include <vector>
#include <list>

void test_choro()
{
  #if 0
  int cnt = 12;
  time_t tnow = time(NULL);
  int idx =( (tnow % 3600)/300 + 1) % cnt;
  std::cout << "current idx == " << idx << std::endl;
  std::vector<int> v1 = {1,2,3};
  std::vector<int> v2;
  v2.swap(v1);
  std::cout << "v1\t" << v1.size()<<std::endl;
  std::cout << "v2\t" << v2.size()<<std::endl;
  #endif
  int *ptr1 = new int(0);
  int *ptr2 = new int(1);
  int *ptr3 = new int(2);
  std::list<int*> vec;
  vec.push_back(ptr1);
  vec.push_back(ptr2);
  vec.push_back(ptr3);
  delete ptr1;
  delete ptr2;
  delete ptr3;
  while(vec.size() > 0)
    {
      auto ite = vec.begin();
      vec.erase(ite);
    }

  std::cout << "*ptr1 == \t" << *ptr1 <<std::endl;
  std::cout << "*ptr2 == \t" << *ptr2 <<std::endl;
  std::cout << "*ptr3 == \t" << *ptr3 <<std::endl;
}
