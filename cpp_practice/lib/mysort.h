/*10 most general sort algorithm
排序算法分类：
比较排序
--交换排序
----冒泡排序
----快速排序
--插入排序
----简单插入排序
----希尔排序
--选择排序
----简单选择排序
----堆排序
--归并排序
----二路归并
----多路归并
非比较排序
--计数排序
--桶排序
--基数排序
*/
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;//swap冲突
// swap element
template<class T>
void myswap(T &e1, T &e2){
  T tmp = e1;
  e1 = e2;
  e2 = tmp;
}
// 1.冒泡排序 bubbleSort
template<class T>
bool bubbleSort(T arr[], size_t m, size_t n){
  // sort arr[m] to arr[m+n-1]
  if(arr == nullptr || n <= 0 || m < 0){return false;}
  for(size_t tail = m+n-1; tail > m; --tail){
    for(int idx = m; idx < tail; ++idx){
      if(arr[idx] > arr[idx+1]){
	T tmp = arr[idx];
	arr[idx] = arr[idx+1];
	arr[idx+1] = tmp;
      }
    }
  }
  return true;
}

// 2.选择排序 selectionSort
template<class T>
bool selectionSort(T arr[], size_t m, size_t n){
  // sort arr[m] to arr[m+n-1]
  // 从后面未排序的序列中选择最小的元素插入到前面已排序元素的末尾
  if(arr == nullptr || m < 0 || n <= 0){return false;}
  size_t arrEnd = m+n;
  for(size_t tail = m; tail < arrEnd; ++tail){
    T currentMinIdx = tail;
    for(size_t idx = tail + 1; idx < arrEnd; ++idx){
      if(arr[currentMinIdx] > arr[idx]){currentMinIdx = idx;}
    }
    if(currentMinIdx != tail){//arr[tail]的元素不是最小的，那么把最小的元素和tail位置的元素交换
      T tmpVal = arr[tail];
      arr[tail] = arr[currentMinIdx];
      arr[currentMinIdx] = tmpVal;
    }
  }
  return true;
}

// 3.插入排序 insertionSort
template<class T>
bool insertionSort(T arr[], size_t m, size_t n){
  // 从后面未排序的序列中选择第一个元素，插入到前面已经排序的序列中
  if(arr == nullptr || m < 0 || n <= 0){return false;}
  size_t arrEnd = m + n;
  for(size_t tail = m; tail < arrEnd-1; ++ tail){
    // tail是已排序序列尾
    for(size_t idx = tail + 1; idx > m; --idx){
      if(arr[idx] < arr[idx-1]){
	myswap(arr[idx], arr[idx-1]);
      }
      else{break;}
    }
  }
  return true;
}

// 4.希尔排序 shellSort
template<class T>
bool shellCore(T arr[], size_t m, size_t n, int tk){
  if(tk <= 0){return false;}
  for(size_t iHead = 0; iHead < tk; ++iHead){
    size_t iNum = (n-1 - iHead) / tk + 1;//iHead:间隔为tk的序列的头部序号， iNum:序列元素数量
    size_t arrEnd = m + n;
    for(size_t tail = iHead; tail < arrEnd-tk; tail+=tk){
      for(size_t idx = tail + tk; idx > iHead; idx-=tk){
	if(arr[idx] < arr[idx-tk]){ myswap(arr[idx], arr[idx-tk]); }
	else{break;}
      }
    }
  }
  return true;
}
template<class T>
bool shellSort(T arr[], size_t m, size_t n){
  // 根据增量序列t1 t2 .. tk 进行k 次排序(使用插入排序)
  if(arr == nullptr || m < 0 || n <= 0){return false;}
  vector<int> TK;
  TK.push_back(10); TK.push_back(4); TK.push_back(2);TK.push_back(1);
  for(auto it : TK){ shellCore(arr, m, n, it); }
  return true;
}

// 5.归并排序 mergeSore
template<class T>
void mergeCore(T arr[], size_t m, size_t n){// m,n是首尾元素位置
  if(m == n){return;}
  size_t mid = (m+n)/2;
  mergeCore(arr, m, mid);
  mergeCore(arr, mid+1, n);
  // 2路归并
  vector<T> tmp;
  size_t idx1 = m, idx2 = mid+1;
  while(idx1 <= mid && idx2 <= n){
    if(arr[idx1] < arr[idx2]){
      tmp.push_back(arr[idx1]);
      ++idx1;
    }
    else{
      tmp.push_back(arr[idx2]);
      ++idx2;
    }
  }
  while(idx1 <= mid){tmp.push_back(arr[idx1++]);}
  size_t num = tmp.size();//需要复制到arr中的元素数量
  for(size_t idx = 0; idx < num; ++idx){arr[idx+m] = tmp[idx];}
}

template<class T>
bool mergeSort(T arr[], size_t m, size_t n){
  //
  if(arr == nullptr || m < 0 || n <= 0){return false;}
  mergeCore(arr, m, m+n-1);
  return true;
}

// 6.快速排序 qucikSort
template<class T>
int myPartition(T arr[], int m, int n){// m,n是arr首/尾
  //将序列分成两部分，并返回分割点，使得左边的元素不大于分割点，右边元素大于分割点
  if(m == n){ return m; }
  int pviot = (m+n)/2;
  T pVal = arr[pviot];
  int left = m, right = n;
  while(left < right){
    while(arr[right] > pVal){--right;}
    if(right > pviot){
      arr[pviot] = arr[right];
      arr[right] = pVal;
      pviot = right;
    }
    while(arr[left] <= pVal){++left;}
    if(left < pviot){
      arr[pviot] = arr[left];
      arr[left] = pVal;
      pviot = left;
    }
  }
  return pviot;
}

template<class T>
void quickSortCore(T *arr, int m, int n){
  // 快排
  if(m >= n){return;}
  int pviot = myPartition(arr, m, n);
  quickSortCore(arr, m, pviot-1);
  quickSortCore(arr, pviot+1, n);
}

template<class T>
bool quickSort(T arr[], int m, int n){
  //调用快排函数，处理边界情况
  if(arr == nullptr || m < 0 || n <= 0){return false;}
  quickSortCore(arr, m, m+n-1);
  return true;
}

// 7.堆排序 heapSort

template<class T>
class myHeap{//堆，提供构造大顶堆和删除堆顶元素以及排序方法
 public:
 myHeap(T arr[], size_t _m, size_t _n) :arr(arr), m(_m), n(_m+_n-1), heapTail(n){}
  ~myHeap(){}
  void buildMaxTopHeap(){// m,n是数组首尾
    size_t tail = n - m;//cout << "tail ==" << tail << endl;
    size_t numOfNode = (tail+1)/2 - 1;//cout << "numOfNOde ==" << numOfNode << endl;
    for(int iNode = numOfNode; iNode >= 0; --iNode){
      size_t left = 2*iNode + 1, right = 2*iNode + 2;
      if(right > tail){
	if(arr[iNode+m] < arr[left+m]){myswap(arr[iNode+m], arr[left+m]);}
      }
      else{
	if(arr[right+m] < arr[left+m]){
	  if(arr[iNode+m] < arr[left+m]){ myswap(arr[iNode+m], arr[left+m]); }
	}
	else{
	  if(arr[iNode+m] < arr[right+m]){ myswap(arr[iNode+m], arr[right+m]); }
	}
      }
    }
  }
  void deleteTop(){
    if(heapTail < m){return;}
    if(heapTail == m){--heapTail;return;}
    swap(arr[m], arr[heapTail]);
    --heapTail;
    size_t num = heapTail - m;
    size_t top = 0;
    while(2*top+1 <= num){
      size_t left = 2*top+1, right = 2*top+2;
      if(right > num){
	if(arr[top+m] < arr[left+m]){ swap(arr[top+m], arr[left+m]); top = left;}
	else{break;}
      }
      else{
	if(arr[left+m] < arr[right+m]){
	  if(arr[top+m] < arr[right+m]){ swap(arr[top+m], arr[right+m]); top = right;}
	  else{break;}
	}
	else{
	  if(arr[top+m] < arr[left+m]){ swap(arr[top+m], arr[left+m]); top = left;}
	  else{break;}
	}
      }
    }
  }

  void sort(){
    buildMaxTopHeap();
    for(size_t i = m; i < n; ++i){
      deleteTop();
    }
    heapTail = n;
  }
 private:
  T *arr;
  size_t m;
  size_t n;
  size_t heapTail;
};

template<class T>
bool heapSort(T arr[], size_t m, size_t n){
  myHeap<T> myheap(arr, m, n);
  // myheap.buildMaxTopHeap();
   myheap.sort();
  return true;
}


// 8.计数排序 countingSort
//template<class T>
bool countingSort(int arr[], size_t m, size_t n){
  //find minimum and maximum element
  if(arr == nullptr || m < 0 || n <= 0){return false;}
  int localMin = arr[m], localMax = arr[m];
  size_t arrEnd = m+n;
  for(size_t idx = m; idx < arrEnd; ++idx){
    if(arr[idx] > localMax){localMax = arr[idx];}
    else if(arr[idx] < localMin){localMin = arr[idx];}
  }
  //cout << "minimum ==" << localMin << "  maxiimum == " << localMax << endl;
  //count
  vector<int> count(localMax-localMin+1, 0);
  for(size_t idx = m; idx < arrEnd; ++idx){
    ++count[arr[idx] - localMin];
  }
  //
  size_t idx = m;
  for(size_t i = 0; i < count.size(); ++i){
    for(size_t j = 0; j < count[i]; ++j){arr[idx] = i + localMin; ++idx;}
  }
  return true;
}

// 9.桶排序 bucketSort
template<class T>
class ListNode{
 public:
  ListNode<T>() {next = nullptr;}
  ListNode<T>(T  _data): data(_data){ next = nullptr; }
  //ListNode<T>(T _data): data(_data) { next = nullptr; }
  //ListNode<T>(const T _data) { data = _data; next = nullptr;}
  ListNode<T>(ListNode<T>* _node) {next = _node->next; data = _node->data;}
  
  ListNode<T>* next;
  T data;
};

template<class T>
class List{
 public:
  List<T>(){
    head = new ListNode<T>();
    tail = new ListNode<T>();
    head->next = tail;
  }
  ~List<T>(){
    ListNode<T>* cur = head->next;
    while(head != tail){
      delete head;
      head = cur;cur = cur->next;
    }
    delete tail;
  }
  ListNode<T>* head;
  ListNode<T>* tail;
  void insert(ListNode<T>* node){
    // if(head->next == tail){head->next = node; node->next = tail; return;}
    ListNode<T>* cur = head;
    while(cur->next != tail){
      if(cur->next->data < node->data){
	cur = cur->next;
      }
      else{
	node->next = cur->next;
	cur->next = node;
	return;
      }
    }//end while
    node->next = tail;
    cur->next = node;
    return;
  }

  void display(){
    cout << "list == " << endl;
    ListNode<T>* cur = head->next;
    while(cur != tail){cout << "--" << cur->data << endl; cur = cur->next;}
  }
};

void testList(){
  ListNode<int> *node1 = new ListNode<int>(1);
  ListNode<int> *node2 = new ListNode<int>(2);// node2->data = 2;
  ListNode<int> *node3 = new ListNode<int>(3);// node3->data = 3;
  cout << "link1&2" << endl;
  node1->next = node2;
  cout << "link2&3" << endl;
  node2->next = node3;
  List<int> listh; cout << "listh" << endl;
  listh.head->next = node1;
  node3->next = listh.tail;
  cout << "start" << endl;
  listh.display();
}
//template<class T>
bool bucketSort(int arr[], size_t m, size_t n){
  int bucketNum = 5;
  vector<List<int>> buckets(bucketNum);
  size_t arrEnd = m+n;
  int localMin = arr[m], localMax = arr[m];
  for(size_t idx = m; idx < arrEnd; ++idx){
    if(arr[idx] < localMin){localMin = arr[idx];}
    else if(arr[idx] > localMax){localMax = arr[idx];}
  }
  int bucketRange = (localMax-localMin)/bucketNum + 1;
  //cout << "size of = " << buckets.size() << endl;
  for(size_t idx = m; idx < arrEnd; ++idx){
    //cout << idx << endl;
    ListNode<int>* node = new ListNode<int>(arr[idx]);
    // cout << idx << " : " << node->data << endl;
    buckets[(arr[idx] -localMin)/ bucketRange].insert(node);
  }

  size_t idx = m;
  for(auto iB = buckets.begin(); iB != buckets.end(); ++iB){
    ListNode<int>* cur = iB->head->next;
    while(cur != iB->tail){
      arr[idx++] = cur->data;
      //cout << " arr[" << idx << "]" <<"==" <<cur->data << ";" ;
      cur = cur->next;
    }
  }
  
}


// 10.基数排序 radixSort
// 


// TEST
void testSort(size_t num = 3000, int randRange = 4000);
