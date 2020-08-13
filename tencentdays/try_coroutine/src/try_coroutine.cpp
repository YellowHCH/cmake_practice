#include "try_coroutine.h"
#include <string.h>
#include <iostream>
#include <vector>
#include <list>

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

void print_coroutine(char *argv[])
{
        //std::cout << "coroutine: " << argv[1] << std::endl;
        //std::cout << "cwd: " << argv[0] << std::endl;
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
        for(int i = 0; i < n; ++i){
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



