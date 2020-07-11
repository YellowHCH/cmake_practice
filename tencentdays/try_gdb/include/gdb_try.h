#pragma once

#include <iostream>
#include <time.h>

namespace hch{

#define TIMEOUT_CHECK_MESSAGEID_CNT  24

#define GET_INSERT_TIMEOUT_INDEX(TIME)                                  \
        ((TIME % (6*3600)) / 900) % TIMEOUT_CHECK_MESSAGEID_CNT;        \



        void printf_module();

        void test_macro_fun();

        /// ********* try to use gdb **********///
        // gdb exe
        // set args xx1 xx2
        // run 
        void test_gdb_with_args(int argc, char* argv[]);
        void test_gdb_with_core();
}
