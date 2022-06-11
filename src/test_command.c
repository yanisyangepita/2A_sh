#include "../include/test_command.h"

void test_command(int argc, char* argv[])
{
    if (argc >= 1 && argc <= 3)
    {
        // char* options = "r";
        rm(argv[1], /*&options*/NULL);
    }
}
