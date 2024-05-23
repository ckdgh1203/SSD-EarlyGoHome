#include "Shell.cpp"
#include "SsdExcutable.h"
#include "SsdResult.h"

int main(int argc, char* argv[])
{
    SsdExecutable executable;
    SsdResult ssdResult;
    Shell shell{ &executable, &ssdResult, cout};
    shell.run(std::cin);
    return 0;
}