#pragma once

#include <iostream>
#include <time.h>

void test_strace();

void print_func(char* argv[]);

// iOS上在loop里面push_back会报错，在Linux中测试一下
void vectoratloop();
