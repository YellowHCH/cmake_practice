/*
实现一个线程池
线程池对象构造完成之后通过调用函数启动线程池，向线程池添加任务，结束线程池
任务用std::function<void ()>形式定义，所有传入的task使用std::bind()去构造
*/

#include <thread>
#include <pthread.h>
#include <stdio.h>
#include <vector>
#include <functional>
#include <queue>
#include <assert.h>
#include <mutex>
#include <condition_variable>

#define MAX_THREAD_NUM 5

namespace hch
{
class myThreadPool{
    public:
    typedef std::function<void ()> Task;    // 定义任务类型
    public:
    myThreadPool(); //仅初始化一些参数
    ~myThreadPool();
    void setMaxTaskSize(size_t num){if(num < 0) return; maxTaskSize = num;} // 设置最大任务排队数量，用来控制任务的添加速度

    void start(int num);      // 根据参数启动指定数量的线程，由MAX_THREAD_NUM 限制最大线程数量，启动后即开始工作
    void addTask(Task task);  // 向任务队列中添加任务
    void joinThreads();       // 等待所有线程结束再退出当前主线程
    private:
    void threadRun();   // 线程执行的主程序，由start()函数调用
    bool taskFull();    // 判断任务队列是否排满了，辅助用户像线程池添加任务
    void stop();        // 结束线程的工作
    Task takeTask();    // 线程调用这个函数从任务队列中获取任务
    bool taskQueueEmpty();  // 判断任务队列是否空，辅助线程去获取任务

    private:
    size_t numOfThread; // 启动的线程数量
    size_t maxTaskSize; // 任务队列中最大任务数量
    
    std::vector<std::thread> threads_;              // 线程池集合
    std::queue<Task> taskQueue_;                    // 任务队列
    std::mutex TaskQueue_mutex;                     // 保护任务队列，isLooping等变量的互斥量
    std::condition_variable waitTaskQueueNotFull;   // 任务管理中等待任务队列可添加的信号量
    std::condition_variable waitTaskQueueNotEmpty;  // 线程池等待任务时任务队列可获取的信号量
    bool isLooping;                                 // 指示线程池是否工作的判据，结束线程池的channel
    
};



}
// 测试线程池
void test_myThreadPool();
