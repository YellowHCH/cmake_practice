#include "gdb_try.h"
#include <list>
#include <stdio.h>
#include <unistd.h>

void test_strace()
{
  time_t tnow = time(NULL);
  std::list<int> myList;
  for(size_t i = 0; i < 200; ++i)
    {
      myList.push_front(i);
      sleep(1);
    }
  sleep(1);
}

void print_func(char* argv[])
{
  std::cout << "__fun__ " <<  argv[0] << std::endl;
}
