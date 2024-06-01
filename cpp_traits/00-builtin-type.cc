#include <iostream>
#include <stdlib.h>

template <typename T> struct Iter {
  typedef T value_type; // decl builtin type

  Iter() = default;

  Iter(const T val) : _val(val) {}

  T operator*() { return _val; }

  T _val;
};

// One could get value type from Iter class through I::value_type.
template <typename I> typename I::value_type foo(I iter) { return *iter; }

// traits value_type from I.
template <typename I> struct iterator_traits {
  typedef typename I::value_type value_type;
};

// traits value_type from I, partitial template for pointer.
template <typename I> struct iterator_traits<I *> {
  typedef I value_type;
};

//
template <typename I> typename iterator_traits<I>::value_type foo2(I iter) {
  return *iter;
}

int main() {
  Iter<int> iter(int(123));
  std::cout << foo(iter) << "\n";

  Iter<double> iter2(double(123.321));
  std::cout << foo2(iter2) << "\n";

  float iter3 = 0.996;
  std::cout << foo2(&iter3) << "\n";

  return 0;
}
