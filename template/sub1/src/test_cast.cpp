#include "test_cast.h"
#include <typeinfo>
template<typename T1, typename T2>
class type_cmp{
    public:
    type_cmp(T1 x1, T2 x2){}
    //typedef type1 T1;
    //typedef type2 T2;
    bool val(){
        type_comp<T1, T2> tp;
        return tp.val;
    }

   

};




void test_cast(){
    // static_cast
    int intval1 = 10;
    int intval2 = 3;
    std::cout << "static_cast : 10/3 == " << static_cast<double>(intval1) / intval2 << std::endl;
    
    // const_cast
    const int const_val = 100;
    std::cout << "const_cast : const_val == " << const_val << "++const_val == " << ++*const_cast<int*>(&const_val) << std::endl;
    // dynamic_cast
    Base *pb = new Base();
    std::cout << "converse from Base to Derived class" << std::endl;
    Derived *pd = dynamic_cast<Derived*>(pb);
    if(pd == nullptr){
        std::cout << "failer" << std::endl;
    }
    else{
        pd->foo();
    }
    
    std::cout << "converse from Derived to Base class" << std::endl;
    pb->foo();
    pb = dynamic_cast<Base*>(pd);
    if(pb == nullptr){
        std::cout << "failer" << std::endl;
    }
    else{
        pb->foo();
    }
    delete pb;
    delete pd;
    pb = nullptr;
    pd = nullptr;

    Base *pd2 = new Derived();
    std::cout << "converse from Derived to Base class" << std::endl;
    pd2->foo();
    Derived *pb2 = dynamic_cast<Derived*>(pd2);
    if(pb2 == nullptr){
        std::cout << "failer" << std::endl;
    }
    else{
        pb2->foo();
        pd2->foo();
        Derived *pd3;
        type_cmp<Base*, Derived*> tp(pb2, pd3); 
        if(typeid(pb2) == typeid(pd3)){
            std::cout << "conversion successful" << std::endl;
        }
        else{
            std::cout << "conversion failer" << std::endl;
        }
    }
    delete pb2;
    delete pd2;
    pb = nullptr;
    pd = nullptr;

    // reinterpret_cast
    int16_t intval_16 = -100;
    uint32_t uintval_32 = *reinterpret_cast<uint32_t*>(&intval_16);
    std::cout << "reinterpret_cast : " << intval_16 << " to " << uintval_32 << std::endl;
    return;
}