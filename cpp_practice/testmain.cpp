#include <iostream>
#include "lib/mysort.h"
using namespace std;

int main(){
  /*int vec[10] = {3,-19,5,1,99,0,4,-1,2,-100};
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
  std::cout <<"bucketSort" <<  std::endl;*/
  testSort();
  testSort(1000,2000);
  testSort(5000,8000);
  testSort(10000,15000);
  return 0;
}
