#include "Shell.h"
#include "SsdExcutable.h"
#include "SsdResult.h"

string getDirectoryPath(string filePath);
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
        string runnerListFilePath = getDirectoryPath(__FILE__) + "./" + runnerListFile;
        shell.runRunner(runnerListFilePath);
    }

    return 0;
}

string getDirectoryPath(string filePath)
{
    size_t lastSlashPos = filePath.find_last_of('/\\');
    string dirPath = filePath;
    if (lastSlashPos != std::string::npos)
    {
        dirPath = filePath.substr(0, lastSlashPos);
    }
    return dirPath;
}