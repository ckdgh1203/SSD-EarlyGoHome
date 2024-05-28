#include "Shell.cpp"
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
        string fileName(argv[1]);
        string filePath = "../../Data/" + fileName;
        shell.run(filePath);
    }

    return 0;
}