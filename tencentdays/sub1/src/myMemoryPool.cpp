#include "myMemoryPool.h"

// myMemoryBlock
void myMemoryBlock::InitMemoryBlock(){
    //void *unitPtr = (void*)(&unitSeg) ;
    for(uint idx = 0; idx < numUnit; ++idx){
        void *unitPtr = (void*)(&unitSeg) + (idx*(unitSize + 2));   // 指向第idx个单元的起始位置
        *(short*)unitPtr = short(idx+1);    // 下一个空闲单元的编号
    }
}


// myMemoryPool
template<typename T>
T* myMemoryPool<T>::getMemory(){
    // 从blocks_中搜索空闲内存
    if(blocks_.empty()){
        creatBlock();
        return getMemory();
    }
    myMemoryBlock* mb = blocks_.front();
    while(mb->numFree <= 0 && mb != nullptr){
        mb = mb->pNext;
    }
    if(mb == nullptr){
        creatBlock();
        return getMemory();
    }
    else{
        void* unitPtr = (void*)(mb->unitSeg) + mb->nFirst * (objSize + 2);
        mb->nFirst = *(short*)unitPtr;  // 更新当前内存块的第一个空闲内存单元编号
        --(mb->numFree);                // 更新当前内存块的剩余空闲单元数量
        
        return (T*)(unitPtr + 2);       // 滤出两个字节的编号
    }
}

template<typename T>
bool myMemoryPool<T>::returnMemory(T* ptr){
    ptr = (void*)ptr - 2;
    // 找到所属的内存块
    myMemoryBlock *mb = nullptr;
    for(auto block : blocks_){
        if((void*)(block->unitSeg) <= (void*)ptr && (void*)(block->unitSeg) + blockSize > (void*)ptr){
            mb = block;
            // 计算编号
            uint num = ( (size_t)ptr - (size_t)&(mb->unitSeg) ) / objSize;
            *(short*)ptr = short(mb->nFirst);   // 将内存块的第一个空闲单元编号赋予到ptr的前两个字节
            mb->nFirst = num;                   // 更新内存块的第一个空闲单元为ptr所在单元
            return true;
        }
    }
    // 运行到这里说明这个内存单元不在内存池中
    std::cerr << "ptr not belong to current memorypool";
    return false;
}

template<typename T>
myMemoryBlock* myMemoryPool<T>::creatBlock(){
        // 从当前内存池去更新内存块的单元数量和单元对象size大小
        myMemoryBlock::numUnit = numUnit;
        myMemoryBlock::unitSize = objSize;
        myMemoryBlock *mb = new myMemoryBlock();    // new出一个新内存池
        if(!blocks_.empty()){   // 当内存池中已经有内存块，那么将前一块内存块的pNext指针指向最新的内存块
            myMemoryBlock *mbLast = blocks_.back();
            mbLast->pNext = mb;
        }
        blocks_.push_back(mb);  // 将内存块添加到blocoks_中
        ++numBlocks;            // 更新内存池对内存块数量的记录
        return mb;
    }
// 内存池的析构，释放每一个内存块
template<typename T>
myMemoryPool<T>::~myMemoryPool(){
    for(auto block : blocks_){
        delete block;
    }
}

// test
void test_mymemorypool(){
    unsigned long numunit = 0;
    unsigned long unitsize = 0;
    myMemoryBlock *mb = new myMemoryBlock();
    //myMemoryBlock mb(0,0);
    mb->printInfo();
    
    delete mb;
}


