/// more efective c++

// item 1 : 指针和引用的区别
#if 0
* 引用只是alias，必须指向实体而非nullptr，所以reference在创建时需要指向对象；
* 引用不会指向空值，意味着引用在使用时不需要检查合法性，所以效率高一点
* 重载操作符时应该使用引用
#endif

// item 2 : 使用c++风格的类型转换
#if 0
static_cast<to_type>(from_obj);
const_cast<to_type>(from_obj);   // remove const property
dynamic_cast<to_type>(from_obj); // 用于安全的沿着类的继承关系向下转换，即从base->derived
reinterpret_cast<to_type>(from_obj); // 函数指针类型间转换
#endif

// item 3 : 不要对数组使用多态
#if 0
* 这里的原因大概是派生类的内存布局和基类不同，在进行数组的指针自加时可能会出错,++ptr;
#endif

// item 4 : 避免使用缺省的构造函数
#if 0
* 遇到过的一个问题是在全局变量初始化对象数组，无法传入参数
#endif

// item 5 : 谨慎定义类型转换函数
#if 0
* 避免编译器隐式的调用这些转换函数或单参数构造函数，造成无法预料的问题
* 单参数构造函数的隐式转换可以通过explicit关键字避免
#endif

// item 6 : ++val && val++
#if 0
* ++val 是自加后返回引用，所以可以用于连续赋值
* val++ 是先拷贝一个临时对象返回，然后自加
#endif

// item 7 : 不要重载 && || ,
#if 0
* 区别在于重载后操作符是函数，会对逻辑中的每个sub计算，但&& || ， 等是短路求值的，满足了条件后后面的就不会计算了
* (ptr != nullptr && *ptr == 1) -> 这不用担心后面的条件会出错，但在函数重载后不得行;
#endif

// item 8 : new && delete
#if 0
* new contains two operators, operate new and construct. the front one allowcate memory for obj, the back one construct obj by call constructefunction;
* placement new, construct object at current memory site;
* delete means deconstruct and operate delete memory;
* new arrays : type *ptr = new type[number]; operate new[] is called; 
#endif





