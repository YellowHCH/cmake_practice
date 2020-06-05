 #include <iostream>
 #include <pthread.h>
 #include <stdio.h>
 //#include <thread>
 //#include <mutex>

 #include <dirent.h>
 #include <sys/types.h>
 #include <string.h>
 #include <string>
 #include <vector>
 #include <iterator>

// for multi process
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include <boost/date_time/gregorian/gregorian.hpp>

int printDir(const char * dirname)
{
        ;
	// open dir fd
	DIR *dir = opendir(dirname);
	struct dirent *entry;
	int entry_cnt = 0;
	while( 0 != (entry = readdir(dir)) )
	  {
	    if( !strcmp(".", entry->d_name)  || !strcmp( ".." , entry->d_name) )
	      {
		continue;
	      }
	    ++entry_cnt;
	    printf("%d : entry name %s\n", entry_cnt, entry->d_name);
	  }

	printf("there are %d file(s) in %s dir\n", entry_cnt, dirname);
	closedir(dir);
	return 0;
}

std::vector<char *> getFilename(const char * dirname)
{
        ;
	std::vector<char *> res(0);
	DIR *dir = opendir(dirname);
	struct dirent *entry;
	int entry_cnt = 0;
	while( 0 != (entry = readdir(dir)) )
	  {
	    if( !strcmp(".", entry->d_name)  || !strcmp( ".." , entry->d_name) )
	      {
		continue;
	      }
	    ++entry_cnt;
	    //printf("%d : entry name %s\n", entry_cnt, entry->d_name);
	    res.push_back(entry->d_name);
	  }
	for(std::vector<char *>::iterator ite = res.begin(); ite != res.end(); ++ite)
	{
	  printf("filename : %s\n", *ite);
	}

	printf("there are %d file(s) in %s dir\n", entry_cnt, dirname);
	closedir(dir);
	return res;
}

struct PthreadStruct {
        ;
public:
  PthreadStruct(const char * dir) : dirname(dir)
  {}
  const char *dirname;
};

// pthread_mutex_lock(pthread_mutex_t *)
pthread_mutex_t  data_mutex;
int data;


void *pThreadFoo(void *param)
{
        ;
	PthreadStruct* p = (PthreadStruct *)param;
	for(int idx = 0; idx < 10; ++idx){
	  pthread_mutex_lock(&data_mutex);
	  ++data;
	  printf("this thread : %d,********************* data == %d\n", (int)pthread_self(), data);
	  printDir(p->dirname);
	  pthread_mutex_unlock(&data_mutex);
	}
	
}


//std::mutex data_mutex;
//int data = 0;

/*void pThreadFoo2(PthreadStruct *p)
{
        ;
	//PthreadStruct* p = (PthreadStruct *)param;
	for(int idx = 0; idx < 10; ++idx){
	  std::lock_guard<std::mutex> guard(data_mutex);
	  printDir(p->dirname);
	  ++data;
	  printf("in thread %d, data == %d\n", get_id(), data)
	}
}
*/

// process
static void sig_child(int signo)
{
        ;
	pid_t pid;
	int stat;
	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
	  {
	    printf("child process %d terminated\n", pid);
	  }
}

int test_process()
{
        ;
	printf("begin test process\n");
	pid_t child_pid;
	// deal child terminated singal
	signal(SIGCHLD, sig_child);

	child_pid = fork();
	if( child_pid < 0){
	  printf("create child process failer\n");
	  return -1;
	}
	else if(child_pid == 0)
	  {
	    // for child process
	    printf("this is child process\n");
	    exit(0);
	  }
	else
	  {
	    // for parent process
	    printf("this is parent process\n");
	    sleep(1);
	    system("ps -o pid,ppid,state,tty,command");
	    //system("./test");
	  }
	return 0;
}

// write file
#include <iostream>
#include <fstream>
#include <ctime>

int write2file()
{
  ;
  printf("start write file\n");
  std::ofstream writeResp;
  writeResp.open("/root/tmp/logfile.log", std::ios::app);
  std::time_t t = std::time(0);
  
  writeResp << "current time : " << t << std::endl;
  return 0;
}

// time
#include <ctime>
#include <string>
int test_ctime()
{
  time_t tnow = time(0);
  tm *gmtm = gmtime(&tnow);
  char log[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  snprintf(log, sizeof(log)-1, "year: %d mon: %02d day: %02d", gmtm->tm_year + 1900, gmtm->tm_mon + 1, gmtm->tm_mday);
  //std::cout << "year: " << gmtm->tm_year + 1900 << " mounth: " << (gmtm->tm_mon + 1) << " day: " << gmtm->tm_mday << std::endl;
  ;
  std::cout << log << std::endl;
  return 0;
}

//
#include <thread>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <condition_variable>
#include <functional>
#include <vector>

std::mutex value_mutex;
std::mutex cond_mutex;
std::condition_variable cond_;
bool ready = false;
bool process = false;

// function
std::function<const int()> GetConstFourteenFour ([]{return 44;});

class MyClass{
public:
  MyClass(int num): m_num(num){}
  int add_and_print(int num)
  {
    std::unique_lock<std::mutex> guard(num_mutex);
    m_num += num;
    guard.unlock();
    std::cout << "new num == " << m_num <<std::endl;
    return m_num;
  }

  int adds_and_print(std::vector<int> &arr)
  {
    std::unique_lock<std::mutex> guard(num_mutex);
    for(auto ite : arr)
    {
      m_num += ite;
    }
    guard.unlock();
    std::cout << "res of adds_and_print -> " << m_num << std::endl;
    return m_num;
  }
  
private:
  std::mutex num_mutex;
  int m_num;
};

MyClass myConst(99);
std::vector<int> myArr = {1,2,3};
using std::placeholders::_1;
std::function<int (int)> pAdd_and_Print = std::bind(&MyClass::add_and_print, &myConst, _1);
std::function<int () > pAdds_and_Print = std::bind(&MyClass::adds_and_print, &myConst, myArr);

int test_function()
{
  std::cout << "start test function\n";
  std::cout << "pAdd_and_Print -> "  << pAdd_and_Print(1) << std::endl;
  std::cout << "pAdds_and_Print -> " << pAdds_and_Print() << std::endl;
}

// 
void foo()
{
  {
    std::lock_guard<std::mutex> guard(value_mutex);
    std::cout << "thread::foo pid == " << GetConstFourteenFour() << "****" <<std::this_thread::get_id() << "\n";
  }
  std::cout << "foo1 wait for foo2 to begin\n";
  // std::lock_guard is not useful
  // std::lock_guard<std::mutex> gard_cond(cond_mutex);
  std::unique_lock<std::mutex> gard_cond(cond_mutex);
  // wait ready change to true
  #if 0
  // tranditional foamt is
  std::condition_variable cond_(cond_mutex);
  while(ready)
  {
    cond_.wait();
  }
  #endif
  cond_.wait(gard_cond, []{return ready;});
    std::cout << "foo1 wait for 1 second then wake up foo2\n";
  usleep(1000000);
  process = true;
  // unclok the mutex to avoid foo2 block at cond_mutex
  gard_cond.unlock();
  cond_.notify_one();
}

void foo2()
{
  sleep(1);
  {
    std::lock_guard<std::mutex> lk(cond_mutex);
    ready  = true;
  }
  std::cout <<"foo2 wait for foo1" << std::endl;
  cond_.notify_one();
  {
    std::unique_lock<std::mutex> gard_cond(cond_mutex);
    cond_.wait(gard_cond, []{return process;});
  }
  std::cout << "end of foo2"  << std::endl;
}

void foo3()
{
  ;
  
  
}

int test_thread()
{
  std::cout << "start test thread\n";
  int num = 100;
  std::string str = std::to_string(num);
  std::thread mythread1(foo);
  std::thread mythread2(foo2);
  mythread1.join();
  mythread2.join();
  std::cout << "end of test thread\n";
}

/// remove file
#include <cstdio>
#include <fstream>

int creat_file(const std::string& filename)
{
  std::fstream iofile(filename.c_str(), std::ios::in | std::ios::out | std::ios::app);
  if(!iofile.is_open()) {std::cout << "creat/open file failer\n"; return -1;}
  iofile << filename << std::endl;
  char buffer[100];
  std::ifstream ifs;
  ifs.open(filename.c_str(), std::ios::in);
  while(!ifs.eof())
  {
    //iofile.getline(buffer, 100);
    //std::ifstream ifs;
    //ifs.open(filename.c_str(), std::ios::in);
    
    ifs >> buffer;
    std::cout << "buffer:["<< buffer << " ]******* strlen of buffer " << strlen(buffer) << std::endl;
    if(!ifs.eof()){
      ifs.close();
      break;
    }
  }
  iofile.close();
  return 0;
}

int remove_file(const std::string& filename)
{
  if(remove(filename.c_str()))
  {
    std::cout <<"remove file " <<filename << " success\n";
    return 0;
  }
  else
  {
    std::cout << "remove file " << filename << " failer\n";
    return -1;
  }
}

void test_file()
{
  std::cout << "start test file\n";
  const std::string file_ = "tmpfile";
  creat_file(file_);
  remove_file(file_);
  std::cout << "end test file\n";
}

/// lambda
#include <vector>
#include <algorithm>

class myLambda{
public:
  myLambda():local_val(9)
  {
    
  }
  int local_val;
  std::vector<int> myVec = {1,2,0,9,5,8};

  #if 0
  bool cmp(int a, int b)
  {
    return a > b;
  }
  #endif

  struct {
    bool operator()(int a, int b) {return a > b;}
  } cmp;

  int sort_fun()
  {
    std::sort(myVec.begin(), myVec.end(), cmp);
    return 0;
  }

  int sort_lambda()
  {
    std::sort(myVec.begin(), myVec.end(), [](int a, int b) -> bool {return a > b;});
    return 0;
  }

  // only capture this
  // can't use auto in class because ?
  std::function<int (int)> capture_localval = [this](int val)->int{return this->local_val + val; };
  
  void capture_local_val()
  {
   std::cout << "capture_localval : " << capture_localval(9) << std::endl;
  }
  
  void test_myLambda()
  {
    sort_fun();
    sort_lambda();
    capture_local_val();
  }
};


/// singletone
template <typename T>
class Singletone{
public:
  static T* GetInstance()
  {
    std::call_once(single_flag, [&](){Init();});
    return m_Instance;
  }

  static void Init()
  {
    m_Instance = new T();
  }
  void Destory()
  {
    delete m_Instance;
  }

  explicit Singletone(){}
  ~Singletone(){
    Destory();
  }
private:
  static T *m_Instance;
  static std::once_flag single_flag;
  //Singletone(){}
  //~Singletone(){}
};
template <typename T>
T* Singletone<T>::m_Instance = nullptr;

template<typename T>
std::once_flag Singletone<T>::single_flag;

/// c-p
#include <mutex>
#include <condition_variable>
#include <thread>
#include <ctime>
#include <chrono>
#include <fstream>
class CPPattern;
static const int NUMOFVEC = 4;

class CPPattern : public Singletone<CPPattern>{
public:
  CPPattern()
  {
    isRunning = false;
    m_curProducerBufferIdx = 0;
    m_curProducerBuffer = &m_vec[0];
    m_curConsumerBuffer = nullptr;
  }


  bool check_for_buffer()
  {
    std::lock_guard<std::mutex> lg(m_mutex);
    return !m_BufferEmpty || (&m_vec[(m_curProducerBufferIdx + 1) % NUMOFVEC] == m_curConsumerBuffer);
  }

  void Append_Log(std::string& log)
  {
    std::lock_guard<std::mutex> guadr_buffer(m_ProducerLock);
	m_curProducerBuffer->push_back(std::move(log));
	if(m_curProducerBuffer->size() >= MAXVECSIZE)
	  {
	    
	    if(check_for_buffer())
	      {
		// wait for buffer empty
		std::unique_lock<std::mutex> cond_guard(m_mutex);
		m_BufferEmpty = false;
		m_wait_buffer_cond.wait(cond_guard, [this]{return this->m_BufferEmpty;});
	      }
	    m_curConsumerBuffer = m_curProducerBuffer;
	    m_curProducerBufferIdx = (m_curProducerBufferIdx + 1) % NUMOFVEC;
	    m_curProducerBuffer = &m_vec[m_curProducerBufferIdx];
	    m_BufferFull = true;
	    m_cond.notify_one();
	  }
  }
  
  std::function<void()> Producer = [&]()
  {
    for( ; isRunning ; )
    {
      ;
      std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()); 
      //std::time_t tnow = tp.time_since_epoch().count();
      std::time_t tnow = time(0);
      tm *gmtm = gmtime(&tnow);
      char log[100];
      //snprintf(log, sizeof(log), "year: %d mon: %02d day: %02d", gmtm->tm_year + 1900, gmtm->tm_mon + 1, gmtm->tm_mday);
      //std::cout << "gm time: " << log <<std::endl;
      //std::cout << "local time : " << ctime(&tnow) << std::endl;
      usleep(1000);
      {
	std::lock_guard<std::mutex> guadr_buffer(m_ProducerLock);
	std::string tmpStr = std::to_string(tnow);
	//tmpStr += *log + ", " + std::this_thread::get_id() + ", " + "this is thread log";
	snprintf(log, sizeof(log), "year: %d mon: %02d day: %02d ::[pthread_pid: %ld, %s], function: ", gmtm->tm_year + 1900, gmtm->tm_mon + 1, gmtm->tm_mday, std::this_thread::get_id(), __func__);
	tmpStr += log;
	m_curProducerBuffer->push_back(std::move(tmpStr));
	if(m_curProducerBuffer->size() >= MAXVECSIZE)
	  {
	    //std::cout << "full one vec\n";
	    //if(m_vec[m_curProducerBufferIdx + 1) % NUMOFVEC] == m_curConsumerBuffer)
	    //if(!m_BufferEmpty || (&m_vec[(m_curProducerBufferIdx + 1) % NUMOFVEC] == m_curConsumerBuffer) )
	    if(check_for_buffer())
	      {
		// wait for buffer empty
		//std::cout << "buffer full\n";
		std::unique_lock<std::mutex> cond_guard(m_mutex);
		m_BufferEmpty = false;
		m_wait_buffer_cond.wait(cond_guard, [this]{return this->m_BufferEmpty;});
	      }
	    m_curConsumerBuffer = m_curProducerBuffer;
	    m_curProducerBufferIdx = (m_curProducerBufferIdx + 1) % NUMOFVEC;
	    m_curProducerBuffer = &m_vec[m_curProducerBufferIdx];
	    //std::unique_lock<std::mutex> cond_guard(m_mutex);
	    m_BufferFull = true;
	    m_cond.notify_one();
	    //cond_guard.unlock();
	  }
      }
    
    }
  };

  std::function<void()> Consumer = [&]()
  {
    std::ofstream ofs;
    ofs.open("cppattern_vec.log", std::ios::app);
    for(; isRunning; )
    {
      {
	std::unique_lock<std::mutex> cond_guard(m_mutex);
	m_cond.wait(cond_guard, [this]{return this->m_BufferFull;});
      }
      //std::ofstream ofs;
      //ofs.open("cppattern_vec.log", std::ios::app);
      size_t sz_size = m_curConsumerBuffer->size();
      for(auto idx = 0; idx != sz_size; ++idx)
	{
	  //
	  ofs << idx  << " -> " << (*m_curConsumerBuffer)[idx] << std::endl;
	}
      {
	std::lock_guard<std::mutex> lg(m_mutex);
	m_curConsumerBuffer->clear();
	m_BufferEmpty = true;
	m_curConsumerBuffer = nullptr;
      }
      m_BufferFull = false;
      //m_BufferEmpty = true;
      //std::lock_guard<std::mutex> lg(m_mutex);
      //m_curConsumerBuffer = nullptr;
      //lg.unlock();
      //std::cout << "empty one vec\n";
      m_wait_buffer_cond.notify_one();
  }
    ofs.close();
  };

  void run()
  {
    isRunning = true;
  }

  void stop()
  {
    isRunning = false;
  }
  void work_for_seconds(int sec)
  {
    run();
    std::cout << "start run cp\n";
    //std::thread producerThread1(Producer);
    //std::thread producerThread2(Producer);
    //std::thread producerThread3(Producer);
    std::thread consumerThread(Consumer);
    std::thread producerThreads[5];
    for(int i = 0; i < 5; ++i)
    {
      producerThreads[i] = std::thread(Producer);
    }
    
    //std::thread consumerThread();
    
    //producerThread1.detach();
    //producerThread2.detach();
    //producerThread3.detach();
    for(int i = 0; i < 5; ++i)
    {
      producerThreads[i].detach();
    }
    consumerThread.detach();

    sleep(sec);
    std::cout << "stop run cp\n";
    
    stop();
  }

  void test_CPPATERN()
  {
    work_for_seconds(5);
  }

private:
  //static const int NUMOFVEC = 2;
  const int MAXVECSIZE = 100;
  int m_curProducerBufferIdx;
  std::vector<std::string> m_vec[NUMOFVEC];
  std::vector<std::string> *m_curProducerBuffer;
  std::vector<std::string> *m_curConsumerBuffer;
  std::mutex m_mutex;
  std::mutex m_ProducerLock;
  std::condition_variable m_cond;
  std::condition_variable m_wait_buffer_cond;
  bool m_BufferFull = false;
  bool m_BufferEmpty = true;
  bool isRunning;
};

#define ADDLOCALLOG(log)   \
  CPPattern->GetInstance->Append_Log(log);\
  




/// get current stack
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

class BacktraceTest{
public:
  static int getBackTrace()
  {
    int j, nptrs;
    #define SIZE 100
    void *buffer[100];
    char **strings;

    nptrs = backtrace(buffer, SIZE);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
      perror("backtrace_symbols");
      exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
      printf("%s\n", strings[j]);

    free(strings);

    return 0;
  }

  void test_getBacktrace_core1()
  {
    ;
    getBackTrace();
    
  }

  void test_getBacktrace_core2()
  {
    ;
    test_getBacktrace_core1();
  }

  void test_getBacktrace_core3()
  {
    ;
    test_getBacktrace_core2();
  }

  void test_getBacktrace_core4()
  {
    ;
    test_getBacktrace_core3();
  }

  void test_getBacktrace()
  {
    ;
    std::cout << "get function name : " << __func__ << std::endl;
    std::cout << "get complete function info : " << __PRETTY_FUNCTION__ << std::endl;
    test_getBacktrace_core4();
  }
  
private:
};

int main()
{
        ;
	boost::gregorian::date d(boost::gregorian::day_clock::local_day());
	/*
	data = 0;
	const char dirname[] = "./mydir/";
	//printDir(dirname);
	freopen("log.txt", "w", stdout);
	// get file name
	std::vector<char *> files = getFilename(dirname);
	#if 0
	printf("start pthread...........\n");
	const int thread_num = 5;
	pthread_t tid[thread_num];
        PthreadStruct tParma(dirname);
	for(int i = 0; i < thread_num; ++i)
	{
	  int ret = pthread_create(&(tid[i]), NULL, pThreadFoo, (void *)(&tParma) );
	  if(0 != ret){ printf("thread creat failer\n"); }
	}
	//int ret = pthread_create(&tid, NULL, pThreadFoo, (void *)(&tParma) );
	//if(0 != ret){ printf("thread creat failer"); }

	void * status;
	for(int i = 0; i < thread_num; ++i)
	{
	  pthread_join(tid[i], &status);
	}
        //pthread_join(tid, &status);
	printf("wait for thread %d\n", tid);
	#endif

	*/
	// multi process
	#if 0
	int ret = test_process();
	#endif

	#if 0
	write2file();
	write2file();
	#endif
	// std thread
	//std::mutex data_mutex;
	//int data = 0;
	
	//std::thread t1(pThreadFoo2, &tParma);
	//std::thread t2(pThreadFoo2, &tParma);
	//t1.join();
	//t2.join();
	#if 0
	test_ctime();
	#endif

	#if 0
	test_thread();
	#endif
	#if 0
	test_function();
	#endif
	#if 0
	test_file();
	#endif
	#if 0
	myLambda *pmylambda = new myLambda();
	pmylambda->test_myLambda();
	delete pmylambda;
	#endif
	#if 0
	CPPattern* cppat = CPPattern::GetInstance();
	cppat->test_CPPATERN();
	
	#endif

	#if 1
	BacktraceTest backtrace_test;
	backtrace_test.test_getBacktrace();
	#endif
	//pthread_exit(NULL);
	return 0;
}
