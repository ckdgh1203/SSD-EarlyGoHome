#include "Shell.cpp"
#include "SsdExcutable.h"

int main(int argc, char* argv[])
{
    SsdExecutable executable;
    Shell shell{ &executable };
    shell.run(std::cin);
    return 0;
}