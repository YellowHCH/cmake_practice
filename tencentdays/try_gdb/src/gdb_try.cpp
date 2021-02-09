#include "gdb_try.h"
#include <assert.h>
#include <string.h>

namespace hch{
        
        void printf_module()
        {
                std::cout << "this is gdb_try\n";
        }

        void test_macro_fun()
        {
                time_t now = time(0);
                int index = GET_INSERT_TIMEOUT_INDEX(now)
                        std::cout << "is " << index << std::endl;
                for(int i = 1; i < 500; ++i)
                        {
                                now += 60;
                                index = GET_INSERT_TIMEOUT_INDEX(now);
                                std::cout << "is " << i << " : " << index << std::endl;
                        }
        }

        void test_gdb_with_args(int argc, char* argv[])
        {
                assert(nullptr != argv);
                for(int i = 0; i < argc; ++i)
                        {
                                std::cout << "[" << i << "]: " << argv[i] <<std::endl;
                        }
        }

        void test_gdb_with_core()
        {
                std::cout << "generate coredump ...\n";
                int *tmpPtr = nullptr;
                *tmpPtr = 0;
#if 0
                int tt = -1;
                uint16_t tt16 = static_cast<uint16_t>(tt);
                short tf = 0;
                tf = static_cast<short>(tt16);
                /*
                if(tt16 > 0x7FFF)
                        tf = tt16 - 0x10000;
                else
                        tf = tt16;
                */
                std::cout << "int: " << tt << "; uint_16: " <<tt16 << " transfer to int : "<< tf <<std::endl;
                std::cout << "\n\n";
                char sChars[100] = "hello_fhjsehfkwajfjakko_fdejhfbajwkfjk_dewnajkfbjew_fjebjhfbehj_jknawklfjnwmnmnACbs,ma,dm,,";
                char* sStr = new char[100];
                
                sprintf(sStr, "go-%s", sChars);
                std::cout << "sChars[" << strlen(sChars)  <<" ]:" << sChars << "\n";
                std::cout << "sStr[" << strlen(sStr) << "]  :" << sStr << "\n";

                delete [] sStr;
#endif
        }
}
