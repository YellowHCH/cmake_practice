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
