#include <iostream>
#include <stdlib.h>

template <typename ConcreteT> struct TraitBase0 {
  size_t get_id() const {
    auto *concrete = static_cast<const ConcreteT *>(this);
    return concrete->_get_id();
  }

  void set_id(const size_t id) {
    auto *concrete = static_cast<ConcreteT *>(this);
    concrete->_set_id(id);
  }
};

template <typename ConcreteT> struct TraitBase1 {
  size_t get_fake_id() const {
    auto *concrete = static_cast<const ConcreteT *>(this);
    return 2 * concrete->_get_id();
  }

  void set_fake_id(const size_t id) {
    auto *concrete = static_cast<ConcreteT *>(this);
    concrete->_set_id(2 * id);
  }
};

struct Impl : public TraitBase0<Impl>, public TraitBase1<Impl> {
  Impl(const size_t id) : _id(id) {}
  Impl() = default;

  size_t _get_id() const {
    std::cout << "Impl call get_id get [" << _id << "]\n";
    return _id;
  }

  void _set_id(const size_t id) {
    std::cout << "Impl call set_id replace [" << _id << "] with [" << id
              << "]\n";
    _id = id;
  }

  size_t _id;
};

struct Impl2 : public TraitBase0<Impl2>, public TraitBase1<Impl2> {
  Impl2(const size_t id) : _id(id) {}
  Impl2() = default;

  size_t _get_id() const {
    std::cout << "Impl2 call get_id get [" << _id << "]\n";
    return _id / 2;
  }

  void _set_id(const size_t id) {
    std::cout << "Impl2 call set_id replace [" << _id << "] with [" << id
              << "]\n";
    _id = id * 4;
  }

  size_t _id;
};

int main() {
  Impl traits;
  Impl2 traits2;

  std::cout << "s0. " << traits.get_id() << "\n";

  traits.set_id(42);

  std::cout << "s1. " << traits.get_id() << "\n";

  traits.set_fake_id(42);

  std::cout << "s2. " << traits.get_id() << "\n";
  std::cout << "s3. " << traits.get_fake_id() << "\n";

  std::cout << "s4. " << traits2.get_id() << "\n";

  traits2.set_id(42);

  std::cout << "s5. " << traits2.get_id() << "\n";

  traits2.set_fake_id(42);

  std::cout << "s6. " << traits2.get_id() << "\n";
  std::cout << "s7. " << traits2.get_fake_id() << "\n";
}
