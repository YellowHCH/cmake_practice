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
* 如何初始化全局的对象数组 ,定义如: typename obj[num];
* 如果使用typename obj[num] 这种方式显然的是调用了默认构造函数构造了栈上对象，无法调用其他的构造函数;
* 可以用typename *obj[num];声明这些对象的指针，然后在函数体中for{obj[i] = new typename(param);}去构造这些对象，这种写法有点奇怪但是有效。声明的是对象的指针而非直接的对象，因为在其他的函数中关心的只是能否调用到这个对象而不用关心是对象还是对象指针。同样的声明为typename **ppobj; ppobj = new typename*[num]; for{ ppobj[i] = new typename(param);}这和前者一样的道理，但是对象指针构造在堆上。 ;
#endif

// item 9 : 使用析构函数防止内存泄漏
#if 0
* 配合智能指针，由栈上对象去管理资源，资源的声明周期与栈上对象相同，相当于资源会由操作系统自动释放。这其中需用到的是析构函数，即由栈上对象的析构函数去自动结束资源;
* 普通的指针对象不会主动调用析构，而智能指针的智能所在就是在智能指针对象析构时会调用被绑定的普通指针对象的析构函数
* 
#endif

// item 10 : 在构造函数中防止资源泄漏
#if 0
* 问题出现在构造函数运行时发生了错误，这将导致由指针成员指向的对象泄漏，所以在智能指针出现之前需要处处考虑catch异常，将资源进行释放;
* 有了智能指针之后，不用再考虑这些问题
* typename* m_ptr总是需要人工去处理所指向的内存
* shared_ptr<typename> m_smart_ptr是栈上对象，会自动处理所指向的内存;
#endif

// item 11 : 禁止异常传入到析构函数
#if 0
* 析构函数在对象被销毁或者出现异常时调用
* 所以如果在析构函数中捕获异常会出现调用
#endif

// item 12 : 抛出异常 && 传递参数 && 调用虚函数 过程比较
#if 0
* catch异常后的调用是不会再返回到函数的，这和函数调用不同
* catch传值一定是拷贝不是引用，因为catch异常后参数对象大概率要被析构了，这是生命周期的问题。异步调用也是一样的道理;
* 
#endif

// item 13 : 通过引用捕获异常
#if 0
* 通过指针传递异常对象时，catch处理函数无法得知对象是在堆上申请的还是全局对象或者静态对象，无法处理;
* 通过值传递异常对象时传出传入时都拷贝一次，增大了开销
* 通过引用传递异常对象，拷贝一次，是最佳的选择
#endif

// item 14 : 谨慎使用异常规格
#if 0
...
#endif

// item 15 : 异常处理的系统开销
#if 0
...
#endif

// item 16 : 80-20准则
#if 0
...
#endif

// item 17 : lazy evalution
#if 0
* 典型的应用是写时拷贝技术，
#endif

// item 18 : 预先计算
#if 0
* 对于需要频繁的计算，可以预先对一些内容进行计算以减少执行时的工作;
#endif

// item 19 : 临时对象
#if 0
* 指编译器产生的而非代码显式创建的对象。c++中大量的临时对象显然限制了性能;
* 
#endif

// item 20 : 函数返回值带来开销
#if 0

#endif

// item 21 : 通过重载避免隐式类型转换 
#if 0
* 对于单参数构造函数，编译器可以隐式的调用（除非用explicit修饰）它从而进行类型转换。对类的实现熟悉的话一般不会出错，但是使用类的时候难免出现隐式调用，出现不可预料的结果;
* 重载一些可能造成隐式调用的情况可以避免这种隐式转换，因为编译器可以找到现成的方法，而非自己背地里执行一些操作;

#endif

// item 22 : 重载运算符 = += - -= ... 
#if 0
...
#endif

// item 23 :  
#if 0

#endif

// item 24 : 虚函数 多继承 虚基类 RTTI 的效率代价
#if 0
* 空间代价，为了实现继承，虚继承，编译器需要为class维护一个虚函数表，为每个对象插入虚指针，虚指针的引入导致了构造函数会做一些幕后的工作，占用一些空间;虚基类可以避免派生类重复继承，但是会引入一些额外的虚基类指针;
* RTTI运行效率，显然的，动态绑定需要运行时根据指针指向的对象类型去选择合适的方法。借助虚指针完成这一工作，但是复杂的情况是多继承和虚继承，需要对虚指针进行偏移以移到正确的vptr上，这带来了运行时的开销
#endif

// item 25 : 
#if 0

#endif

// item 26 : 
#if 0

#endif

// item 27 : 
#if 0

#endif

// item 28 : 
#if 0

#endif

// item 29 : 
#if 0

#endif
