#include "Shell.cpp"
#include "SsdExcutable.h"
#include "SsdResult.h"

int main(int argc, char* argv[])
{
    SsdExecutable executable;
    SsdResult ssdResult;
    SsdHelper ssdHelper{ &executable, &ssdResult };
    Shell shell{ ssdHelper, cout};
    shell.run(std::cin);
    return 0;
}