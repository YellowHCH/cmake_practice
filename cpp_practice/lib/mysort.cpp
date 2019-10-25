#include "mysort.h"
#include <iomanip>
void testSort(size_t num, int randRange){
  //size_t num = 3000;//
  //int randRange = 4000;
  int vec[num];
  srand(int(time(0)));
  for(size_t idx = 0; idx < num; ++idx){ vec[idx] = rand()%randRange;}
  cout << "begin.." << endl;
  //test bubbleSort
  int vecBubble[num];
  for(size_t idx = 0; idx < num; ++idx){ vecBubble[idx] = vec[idx]; }
  clock_t timeStart = clock();
  if(!bubbleSort(vecBubble, 0, num)){cout << "failer" <<endl;}
  clock_t timeEnd = clock();
  cout << setw(30) <<"bubble sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;
  //for(size_t idx = 0; idx < num; ++idx){ cout << vecBubble[idx] << ", "<<endl;}
  //test selectionSort
  int vecSelection[num];
  for(size_t idx = 0; idx < num; ++idx){ vecSelection[idx] = vec[idx]; }
  timeStart = clock();
  selectionSort(vecSelection, 0, num);
  timeEnd = clock();
  cout << setw(30) << "selection sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;

  //test insertionSort
  int vecInsert[num];
  for(size_t idx = 0; idx < num; ++idx){ vecInsert[idx] = vec[idx]; }
  timeStart = clock();
  insertionSort(vecInsert, 0, num);
  timeEnd = clock();
  cout << setw(30) << "insertion sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;
  //test shell sort
  int vecShell[num];
  for(size_t idx = 0; idx < num; ++idx){ vecShell[idx] = vec[idx]; }
  timeStart = clock();
  shellSort(vecShell, 0, num);
  timeEnd = clock();
  cout << setw(30) << "shell sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;

  //test merge sort
  int vecMerge[num];
  for(size_t idx = 0; idx < num; ++idx){ vecMerge[idx] = vec[idx]; }
  timeStart = clock();
  mergeSort(vecMerge, 0, num);
  timeEnd = clock();
  cout << setw(30) <<  "merge sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;
  
  //test qucik sort
  int vecQuick[num];
  for(size_t idx = 0; idx < num; ++idx){ vecQuick[idx] = vec[idx]; }
  timeStart = clock();
  quickSort(vecQuick, 0, num);
  timeEnd = clock();
  cout <<setw(30) << "quick sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;
  
  //test heap sort
  int vecHeap[num];
  for(size_t idx = 0; idx < num; ++idx){ vecHeap[idx] = vec[idx]; }
  timeStart = clock();
  heapSort(vecHeap, 0, num);
  timeEnd = clock();
  cout << setw(30) <<  "heap sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;

  //test counting sort
  int vecCount[num];
  for(size_t idx = 0; idx < num; ++idx){ vecCount[idx] = vec[idx]; }
  timeStart = clock();
  countingSort(vecCount, 0, num);
  timeEnd = clock();
  cout <<setw(30) << "counting sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;

  //test bucket sort
  int vecBucket[num];
  for(size_t idx = 0; idx < num; ++idx){ vecBucket[idx] = vec[idx]; }
  timeStart = clock();
  bucketSort(vecBucket, 0, num);
  timeEnd = clock();
  cout << setw(30) << "bucket sort cost : " << double(timeEnd - timeStart)*1000/CLOCKS_PER_SEC << " ms" << endl;

  //test end
  cout << "End..." << endl;
  
}
  
