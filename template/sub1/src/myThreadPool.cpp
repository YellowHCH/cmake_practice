#include "myThreadPool.h"
#include <iostream>
#include <unistd.h> // sleep()

using namespace hch;

myThreadPool::myThreadPool() : numOfThread(0), maxTaskSize(0), isLooping(false) {}
myThreadPool::~myThreadPool(){
    stop(); // 线程池对象被销毁时结束线程池的任务
}
void myThreadPool::start(int num){
    assert(threads_.empty()); // 判断线程池是否已有线程，避免重复开启线程池
    if(num > 0){
        if(num > MAX_THREAD_NUM) {return ;} // 避免申请太多的线程
        isLooping = true;           // 标识线程进入工作状态
        threads_.reserve(num);      // 为线程池预留足够的空间
        for(size_t i = 0; i < num; ++i){
            // 创建线程，运行线程主函数去执行任务
            threads_.emplace_back(std::thread(std::bind(&myThreadPool::threadRun, this)));
            //threads_.back().join();
        }
    }
}


// 判断任务队列是否排满
bool myThreadPool::taskFull(){
    return maxTaskSize <= taskQueue_.size();
}
// 主进程等待所有线程结束
void myThreadPool::joinThreads(){
    for(size_t i = 0; i < threads_.size(); ++i){
        threads_[i].join();
    }
}
// 向任务队列添加任务
void myThreadPool::addTask(Task task){
    if(threads_.empty()){   // 如果没有申请线程池，那么阻塞的在当前主进程完成这个任务
        task();
    }
    else{
        //std::lock_guard<std::mutex> guard(TaskQueue_mutex);
        std::unique_lock<std::mutex> lk(TaskQueue_mutex);   // 加锁互斥量，保护信号量
        while(taskFull()){  // 避免任务队列中任务太多，限制添加任务的速度
            waitTaskQueueNotFull.wait(lk);  // 等待信号量通知任务队列可添加任务
        }
        assert(!taskFull());
        taskQueue_.push(task);
        waitTaskQueueNotFull.notify_all();  // 通知线程任务队列有任务可做，非空
    }
}
// 判断任务队列是否被取空
bool myThreadPool::taskQueueEmpty(){
    return taskQueue_.empty();
}
// 停止线程池的任务
void myThreadPool::stop(){
    {
        std::unique_lock<std::mutex> lk(TaskQueue_mutex);   // 持有互斥量，保护ilLooping和waitTaskQueueNotEmpty
        isLooping = false;  // 通过改写isLooping 结束线程主函数的循环
        waitTaskQueueNotEmpty.notify_all(); // 通知还在等任务的线程结束等待，这里如果不加上，就可能无法结束所有线程
    }
    joinThreads();  // 主线程等待所有线程结束，不然线程池可能还没结束主进程先销毁了

}

myThreadPool::Task myThreadPool::takeTask(){
    std::unique_lock<std::mutex> lk(TaskQueue_mutex);
    while(taskQueueEmpty()){                // 等待任务队列有任务可取
        waitTaskQueueNotEmpty.wait(lk);
    }
    assert(!taskQueueEmpty());
    myThreadPool::Task task;
    task = taskQueue_.front();
    taskQueue_.pop();
    if(maxTaskSize > 0){
        waitTaskQueueNotFull.notify_all();  // 因为至少有一个线程取走了任务，所以任务队列此时一定可接收任务
    }
    return task;
}

void myThreadPool::threadRun(){
    while(isLooping){
        //std::lock_guard<std::mutex> gd(TaskQueue_mutex);
        //printf("start tast0... \n");
        //printf("start tast1... \n");
        //printf("start tast2... \n");
        //printf("start tast3... \n");
        //sleep(2);
        // 线程主函数，不断取任务，完成任务
        myThreadPool::Task task(takeTask());
        if(task){
            task();
        }
    }
}

void test_myThreadPool(){
    myThreadPool mp;
    std::cout << "start ..." << std::endl;
    mp.start(2);
    mp.joinThreads();
}
