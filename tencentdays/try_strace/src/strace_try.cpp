#include "gdb_try.h"
#include <list>
#include <stdio.h>
#include <unistd.h>
#include <vector>

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

void vectoratloop(){
	std::vector<int> v1;
	int idx = 10;
	while (idx > 0)
	{
		for (int i = 0; i < idx; ++i)
		{
			v1.push_back(i);
		}
		--idx;
	}
	for (auto it : v1)
	{
		std::cout << it << " ";
	}
	return;
}
