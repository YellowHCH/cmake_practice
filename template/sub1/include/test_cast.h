/*
读More Effective C++ , c++类型转换的测试
static_cast, c语言中类型转换的替代品，在编译期对非多态类型进行转换
const_cast, 将常量或易变量转换为其他类型，只能对变量的指针或引用进行操作
dynamic_cast, 用于父类和子类之间的转换
reinterpret_cast, 强制类型转换
*/
#ifndef TEST_CAST_H
#define TEST_CAST_H

#include <iostream>

class Base{
    public:
    virtual void foo(){std::cout << "this is Base class" << std::endl;} 
};

class Derived : public Base{
    public:
    virtual void foo(){std::cout << "this is Derived class" << std::endl;}
};


void test_cast();

#endif