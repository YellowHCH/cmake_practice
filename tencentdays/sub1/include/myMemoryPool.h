/*
设计内存池若干
先设计一个固定对象大小的
*/
#ifndef MY_MEMORYPOOL_H
#define MY_MEMORYPOOL_H

#include <stdlib.h>
#include <iostream>
#include <list>

int unit = 0;
int block = 0;
// 固定大小内存池设计
/*
内存池数据结构，基本结构是内存单元unit，内存块block包含块信息和内存单元，由内存池去调用内存块
*/
// 内存块
class myMemoryBlock{
 public:
    myMemoryBlock() :  numFree(numUnit) , nFirst(0), pNext(nullptr)//, objSize(sizeof(myMemoryBlock))
    {
        //std::cout << "this is constructor " << std::endl;
        // 调用内存块初始化函数给内存单元的后继单元编号赋值
        InitMemoryBlock();
    }
    ~myMemoryBlock(){
        //std::cout << "this is destructor " << std::endl;
    }
    
    // 重载operator new，为内存单元也分配内存，输入的参数只能是size_t类型
    static void* operator new( size_t){
        //std::cout << "this is overload new, sizeof memory is " << sizeof(myMemoryBlock) + numUnit*(unitSize + 2)  << std::endl;
        //return malloc(sizeof(myMemoryBlock) + size_t(numUnit_)*(size_t(unitSize_) + 4));
        return ::operator new(sizeof(myMemoryBlock) + numUnit*(unitSize + 2));
    }

    static void operator delete(void *p, size_t){
        //free(p);
        //std::cout << "this is overload destructor " << std::endl;

        ::operator delete (p);
    }

    // 没有用的函数，测试内存块时打印的信息
    void printInfo(){
        std::cout << "addr of numUnit  is " << &numUnit << std::endl;
        std::cout << "addr of unitSize is " << &unitSize << std::endl;
        std::cout << "addr of numFree  is " << &numFree << std::endl;
        std::cout << "addr of nFirst   is " << &nFirst << std::endl;
        std::cout << "addr of pNext    is " << (void*)&pNext << std::endl;
        //std::cout << "addr of objSize  is " << (void*)&objSize << std::endl;
        std::cout << "addr of unitSeg  is " << (void*)&unitSeg << std::endl;
        std::cout << "size of pointer  is " << sizeof(std::nullptr_t) << std::endl;
    }

 private:
    // 初始化内存块
    void InitMemoryBlock();
 public:
    
    static uint numUnit;       // 内存块中内存单元数量
    static uint unitSize;    // 内存单元size，是被存储对象的大小加上4个字节，4字节记录下一个空闲单元编号，这里用4个字节有点浪费，先这么写
    uint numFree;       // 空闲的内存单元数量
    uint nFirst;        // 第一个空闲内存单元编号，编号从0开始
    myMemoryBlock * pNext;  // 指向下一个内存块
    //uint objSize;       // 因为内存对齐的原因，对象的size有点迷，在计算单元的起始位置时需要用到对象大小
    char unitSeg;       // 作为内存块信息头部与内存单元的分割点
    
};

uint myMemoryBlock::numUnit = 4;
uint myMemoryBlock::unitSize = 4;

// 内存池
template<typename T>
class myMemoryPool{
 public:
    
    myMemoryPool(uint numUint_ = 4) : objSize(sizeof(T)), numBlocks(0) , 
    numUnit(numUint_), blockSize((objSize+2)*numUint_ + sizeof(myMemoryBlock)){
    //myMemoryBlock::numUnit = numUint_;
    //myMemoryBlock::unitSize = objSize;
    // 内存池初始化时创建5个内存块
    for(int i = 0; i < 4; ++i)
        creatBlock();
    }

    ~myMemoryPool();

    
    // 从内存池获得一个固定大小对象内存空间，返回内存地址
    T* getMemory();
    // 从内存池归还内存单元
    bool returnMemory(T* ptr);
 private:
    // 创建新的内存块，并添加到blocks_中
    myMemoryBlock* creatBlock();

    private:

    uint objSize;       // 对象大小
    uint numBlocks;     // 内存块数量，初始化为0
    uint numUnit;       // 内存块中单元数量
    size_t blockSize;    // 内存块大小
    std::list<myMemoryBlock*> blocks_;  // 内存块链表
    
};

void test_mymemorypool();

#endif // MY_MEMORYPOOL_H
