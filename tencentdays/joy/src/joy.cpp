#include "joy.h"

MemCheck::MemCheck(){
	std::cout<< "construct\n";
}
MemCheck::~MemCheck(){
	std::cout << "release\n";
}

void MemCheck::ShowMsg(){
	std::cout << m_sMsg << std::endl;
}


void test_joy(void)
{
	std::cout << "this is joy module\n";
	std::cout << "sizeof string:" << sizeof(std::string) << std::endl;;
	std::vector<int*> vPtr;
	for (int i = 0; i < 10; ++i){
		int *pInt = new int(1);
		int numInt = 2;
		std::cout << "addr:"<< (void*)(pInt) << "\t" << &numInt << std::endl;
		//delete pInt;
		vPtr.push_back(pInt);
	}
	for(auto it : vPtr){
		delete it;
	}
	return;
}

void PtrEle::f()
{
	std::cout << "Base member function\n";
}

void DPtrEle::f()
{
	std::cout << "Derived member function\n";
}

void thread_fun_ptr(std::shared_ptr<PtrEle> p){
	g_Count++;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<PtrEle> localSp = p;
	void *ptr = malloc(1024*1);
//	int num = 0;
//	int *ptr = &num;
//	printf("C style, current thread id:%lu\tg_count:%u\n", std::this_thread::get_id(), g_Count);
	// std io is not thread safe
	static std::mutex io_mutex;
	{
		std::lock_guard<std::mutex> lk(io_mutex);
//		void *ptr = malloc(8);
		std::cout << "current thread id:" << std::this_thread::get_id() << "\tuse_cnt:" << localSp.use_count() << "\tg_Count:" << g_Count << "\tptrAddr:"<< (ptr)<< std::endl;
//		free(ptr);
	}
	free(ptr);
}

void test_ptr()
{
	{
		printf("------------ test unique_ptr--------------\n");
		// make unique_ptr
		std::unique_ptr<PtrEle> upBEle = std::make_unique<PtrEle>();
		std::unique_ptr<PtrEle> upDEle = std::make_unique<DPtrEle>();
		// call member function through unique_ptr
		upBEle->f();
		upDEle->f();
		//PtrEle *pDEle = upDEle.get();		// get pointer form unique_ptr
		//PtrEle *pDEle = upDele.release();	// release ptr from up, ptr donot belong to up any more
		// release one ptr manual
		upDEle.reset();
		// transfer ptr to between up
		std::unique_ptr<PtrEle> upBEle2 = std::move(upBEle);
		upBEle2->f();
		upBEle2.reset();
		// check up whether null
		if (upBEle2 == nullptr){
			std::cout << "unique_ptr reset successfully\n";
		}
		// make up from ptr
		PtrEle * ptr = new PtrEle();
		std::unique_ptr<PtrEle> upptr(ptr);
		//PtrEle * ptr2 = upptr.release();
		std::unique_ptr<PtrEle> upptr2( upptr.release() );
		upptr2->f();
	}

	{
		printf("\n------------test shared_ptr--------------\n");
		std::shared_ptr<PtrEle> spEle = std::make_shared<PtrEle>();
		std::vector<std::thread> vecThr;
		const uint32_t THREAD_NUM = 10;
		for ( int idx = 0; idx < THREAD_NUM; ++idx){
			std::thread thr(thread_fun_ptr, spEle);
			vecThr.push_back(std::move(thr));
		}
		for (auto & thr : vecThr){
			thr.join();
		}
		std::cout << "thread end\n";
		spEle.reset();
		// weak_ptr
		std::shared_ptr<PtrEle> sp = std::make_shared<PtrEle>();
		printf("use_cnt:%d\n", sp.use_count());
		std::weak_ptr<PtrEle> wp = sp;
		printf("use_cnt:%d\n", sp.use_count());
		std::shared_ptr<PtrEle> wk2sp = wp.lock();
		printf("use_cnt:%d\n", sp.use_count());
		if (wk2sp == nullptr){
			printf("get shared_ptr from weak_ptr failure\n");
		}
		else{
			printf("get shared_ptr from weak_ptr success\n");
		}
		wk2sp.reset();
		if (wk2sp == nullptr){
			printf("shared_ptr donot exist anymore\n");
		}
		else{
			printf("shared_ptr still exist\n");
		}
		std::shared_ptr<PtrEle> sp3 = wp.lock();
		if (sp3 == nullptr){
			printf("get shared_ptr from weak_ptr success\n");
		}
		else{
			printf("get shared_ptr from weak_ptr failure\n");
		}
	}
}

// epoll base
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <netinet/in.h>

// create socket and bind to specificed IP:PORT
// return socket for communication
static int socket_bind(const char *IP, int PORT);
// deal with listenfd
const int EPOLL_CONNECT_SIZE = 100;
const int EPOLL_EVENTS_SIZE  = 10; 
static int deal_epoll(int listenfd);
static void process_epoll_events(int epollfd, epoll_event *events, int num, int listenfd);
// epoll unit
static int process_accept(int epollfd, int listenfd);
static int add_event(int epollfd, int fd, int state);
static int del_event(int epollfd, int fd, int state);
static int modify_event(int epollfd, int fd, int state);
// IO socket
static int sock_write(int epollfd, int fd);
static int sock_read(int epollfd, int fd);

void test_epoll_server()
{

}

void test_epoll_client()
{

}

int socket_bind(const char *IP, int PORT)
{
	int listenfd = 0;
	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0) ) == -1)
	{
		perror("ERR: create socket err ");
		exit(1);
	}
	sockaddr_in svraddr;
	bzero(&svraddr, sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	// set and bind IP:PORT
	inet_pton(AF_INET, IP, &svraddr.sin_addr);
	svraddr.sin_port = htons(PORT);
	if (bind(listenfd, (struct sockaddr*)&svraddr, sizeof(svraddr)) == -1){
		perror("ERR: bind IP:PORT failure ");
		exit(1);
	}
	return listenfd;
}

int deal_epoll(int listenfd)
{
	int epollfd;
	epollfd = epoll_create(EPOLL_CONNECT_SIZE);
	add_event(epollfd, listenfd, EPOLLIN);
	struct epoll_event events[EPOLL_EVENTS_SIZE];

	for (;;){
		int event_num = epoll_wait(epollfd, events, EPOLL_EVENTS_SIZE, -1);
		process_epoll_events(epollfd, events, event_num, listenfd);
	}

	close(epollfd);
}

void process_epoll_events(int epollfd, epoll_event *events, int num, int listenfd)
{
	// process each event
	int fd;
	for (int i = 0; i < num; ++i){
		fd = events[i].data.fd;
		
		if (events[i].events & EPOLLERR || events[i].events & EPOLLHUP)
		{
			// sock err or hup
			del_event(epollfd, fd, EPOLLHUP);
			close(fd);
			continue;
		}

		if (fd == listenfd){
			// deal with new conection

		}
		else if (events[i].events & EPOLLIN){
			// deal with readable event

		}
		else if (events[i].events & EPOLLOUT){
			// deal with wruteable event

		}
	}
}

int process_accept(int epollfd, int listenfd)
{
	int clifd;
	struct sockaddr_in cliaddr;
	socklen_t  cliaddrlen;
	clifd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
	if (clifd == -1){
		printf("accept err\n");
		return -1;
	}
	else {
		printf("fd:%d accept new conection %d, ip:%s, port:%d\n", listenfd, clifd, inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
		add_event(epollfd, clifd, EPOLLIN);
	}
}

int add_event(int epollfd, int fd, int state)
{
	epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

int del_event(int epollfd, int fd, int state)
{
	epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

int modify_event(int epollfd, int fd, int state)
{
	epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	return epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}
