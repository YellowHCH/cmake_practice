#include <iostream>
#include "lib/add.h"
#include "lib/sub.h"
#include "lib/mysort.h"
using namespace std;

int main(){
  int num1 = 1999;
  int num2 = 2999;
  int res = myadd(num1, num2);
  cout << "result num2 + num1 == " << res << endl;
  cout << "result num2 - num1 == " << mysub(num2, num1) << endl;
  int vec[10] = {3,-19,5,1,99,0,4,-1,2,-100};
  size_t num = 10;
  for(size_t i = 0; i < num; ++i){
    std::cout << vec[i] << ", " ;
  }
  std::cout << std::endl;
  // bubbleSort(vec, 0, 6);
  // shellSort(vec, 0, 6);
  //mergeSort(vec, 0, 6);
  //quickSort(vec, 0, num);
  //heapSort(vec, 0, num);
  //countingSort(vec, 0, num);
  bucketSort(vec, 0, num);
  for(size_t i = 0; i < num; ++i){                                               
    std::cout << vec[i] << ", " ;                                              
  }                                                                            
  std::cout <<"bucketSort" <<  std::endl;
  return 0;
}
