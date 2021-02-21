#include "try_coroutine.h"
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#if 0
static int & GetNum()
{
        static int num;
        return num;
}

// 合并左右两边可以继续合并的pair
static bool DealNum(std::list<int> & vec, int & count){
        auto node1 = vec.begin();
        if(node1 = vec.end()){return false;}
        auto node2 = node1 + 1;
        while(node2 != vec.end()){
                
        }
}

// 合并第一对相同的代金券
static bool MergeNum(std::list<int> & vec, int & count)
{
        auto node1 = vec.begin();
        if(node1 == vec.end()){return false;}
        auto node2 = node1 + 1;
        while(node2 != vec.end())
        {
                if(*node1 == *node2){
                        *node1 += 1;
                        ++count;
                        vec.erase(node2);
                        node2 = node1 + 1;
                        return true;
                }
                else{
                        node1 = node2;
                        node2++;
                }
        }
        return false;
}
#endif

void print_coroutine(char *argv[])
{
        std::cout << "coroutine: " << argv[1] << std::endl;
        std::cout << "cwd: " << argv[0] << std::endl;
#if 0
        char * src1 = nullptr;
        char des[100] = {0};
        memset(des, 0, sizeof(des));
        int num;
        snprintf(des, sizeof(des)-1, "%s%d", src1, GetNum());
        std::cout << "###" << des << std::endl;
#endif
        const int n = 5;
        std::list<int> listNum;
        for(int i = 0; i < n; ++i){
                listNum.push_back(1);
        }
        
        
}

void test_ucontext()
{
	ucontext_t ctx;
	// get current context, routine will resume at this point
	getcontext(&ctx);

	static int cnt = 0;
	std::cout << "current coroutine cnt: " << cnt++ << std::endl;
	if (cnt > 10) {return;}
//	getcontext(&ctx);
	std::cout << "##" << std::endl;
	// set cts as next task, back to where getcontext be called
	setcontext(&ctx);
	return;
}

void coFun1(char* str)
{
	std::cout << "coFun1 str: " << str << std::endl;
	return;
}

void coFun2()
{
	std::cout << "coFun2" << std::endl;
}

void (*coFun)(void);

void test_ucontext2()
{
	ucontext_t main_ctx, ctx1;
	static char cStack[1024];
	getcontext(&ctx1);
	ctx1.uc_stack.ss_sp = cStack;
	ctx1.uc_stack.ss_size = sizeof(cStack);
	ctx1.uc_link = &main_ctx;
	char str[] = "TENCENT";
	coFun = coFun2; 
	makecontext(&ctx1, (void (*)(void))coFun1, 1, str);

	std::cout << "leave main fun && goto coFun1" << std::endl;
	swapcontext(&main_ctx, &ctx1);
	std::cout << "resume main fun && goto coFun2" << std::endl;
	makecontext(&ctx1, (void (*)(void))coFun, 0);
	swapcontext(&main_ctx, &ctx1);
	std::cout << "end" <<std::endl;
	return;
}

#if 0
struct MultiTreeNode{
        MultiTreeNode(int num, int d = 0, int toRoot) : dis = d{childs.clear();, disToRoot = toRoot;}
        int dis;
        int n;
        int disToRoot;
        std::vector<MultiTreeNode*> childs;
};

void Dis()
{
        int n = 0;
        std::cin >> n;
        //std::vector<int> U, V, W;
        //U.reserve(n-1);
        //V.reserve(n-1);
        //W.reserve(n-1);
        std::vector<std::vector<int>> mMap(n, std::vector<int>(n, 0));
        OB for(int i = 0; i < n; ++i){
                int u, v, w;
                cin >> u, v, w;
                mMap[u][v] = w;
                mMap[v][u] = w;
        }
        //
        std::vector<bool> bIsUsed(n, false);
        bIsUsed[0] = true;
        std::vector<MultiTreeNode*> curLayer;
        MultiTreeNode node(1, 0, 0);
        for(int i = 1; i < n; ++i){
                if(mMap[1][i] != 0){
                        MultiTreeNode * tmpNode(i, mMap[1][i], mMap[1][i] + 0);
                        node.childs.push_back(tmpNode);
                        bIsUsed[i] = true;
                }
        }
        std::vector<MultiTreeNode*> nextLayer;
        curLayer = node.childs;
        whule(!curLayer.empty()){
                for(int i = 0; i < curLayer.size(); ++i){
                        MultiTreeNode* curNode = curLayer[i];
                        int num = curNode->n;
                        for(int idx = 0; idx < n; ++idx){
                                if(mMap[num][idx] != 0 && !bIsUsed[idx]){
                                        MultiTreeNode * tmpNode(idx, mMap[num][idx], mMap[num][idx] + curNode->disToRoot);
                                        curNode->childs.push_back(tmpNode);
                                        bIsUsed[idx] = true;
                                        nextLayer.push_back(tmpNode);
                                }
                        }
                }
                std::swap(curLayer, nextLayer);
        }
        //
        
}
#endif


