#include "Shell.cpp"
#include "SsdExcutable.h"
#include "SsdResult.h"

int main(int argc, char* argv[])
{
    SsdExecutable executable;
    SsdResult ssdResult;
    Shell shell{ &executable, &ssdResult, cout};

    if (argc < 2)
    {
        shell.run(std::cin);
    }
    else
    {
        shell.run(argv);
    }

    return 0;
}