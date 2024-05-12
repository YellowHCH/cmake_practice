#include <stdio.h>

void func_without_restrict(int *a, int *b, int *c) {
  *a += *c;
  *b *= *c;
}

void func_with_restrict(int *__restrict__ a, int *__restrict__ b, int *__restrict__ c) {
  *a += *c;
  *b *= *c;
}

int main() {
  int a = 1, b = 2, c = 3;
  
  printf("Before: a=%d, b=%d, c=%d\n", a, b, c);

  func_without_restrict(&a, &b, &c);
  func_with_restrict(&a, &b, &c);
  
  printf("After: a=%d, b=%d, c=%d\n", a, b, c);
  
  return 0;
}
