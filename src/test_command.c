#include "../include/test_command.h"

void test_command(int argc, char* argv[])
{
    if (argc >= 1 && argc <= 3)
    {
        my_mkdir(argv[1]);
    }
}
