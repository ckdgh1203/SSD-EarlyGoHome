#include "Shell.h"
#include "SsdExcutable.h"
#include "SsdResult.h"

int main(int argc, char* argv[])
{
    SsdExecutable executable;
    SsdResult ssdResult;
    SsdHelper ssdHelper{ &executable, &ssdResult };
    Shell shell{ ssdHelper, cout };

    if (argc < 2)
    {
        shell.run(std::cin);
    }
    else
    {
        string runnerListFile(argv[1]);
        shell.runRunner(runnerListFile);
    }

    return 0;
}