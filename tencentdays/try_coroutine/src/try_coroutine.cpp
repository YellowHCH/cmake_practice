#include "try_coroutine.h"

void print_coroutine(char *argv[])
{
        std::cout << "coroutine: " << argv[1] << std::endl;
        std::cout << "cwd: " << argv[0] << std::endl;
}
