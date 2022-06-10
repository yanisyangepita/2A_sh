#include "../include/test_command.h"

void test_command(int argc, char* argv[])
{
    if (argc > 1 && argc <= 3)
    {
        mv(argv[1], argv[2]);
    }
}
