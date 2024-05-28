#include "Shell.h"

void Shell::run(istream& inputStream)
{
    while (true)
    {
        m_outputStream << "shell> ";

        vector<string> args{};
        parseArguments(inputStream, args);
        
        if (1 > args.size()) continue;

        auto* scriptHandler = m_scriptFactory.create(args[0], m_ssdHelper);
        if (scriptHandler != nullptr)
        {
            m_outputStream << args[0] << " " << scriptHandler->getScriptResult() << "\n";
            delete scriptHandler;
            continue;
        }

        auto* commandHandler = m_commandFactory.create(args[0]);
        if (commandHandler == nullptr)
        {
            m_outputStream << "\nINVALID COMMAND\n";
            continue;
        }

        if (!commandHandler->isValidArgs(args))
        {
            m_outputStream << "\nINVALID COMMAND\n";
            commandHandler->usage();
            continue;
        }

        if (Progress::Done == commandHandler->doCommand(args)) break;
    }
}

void Shell::runRunner(const string & fileName)
{
    string filePath = getDirectoryPath(__FILE__) + fileName;
    ifstream file(filePath);

    if (!(file.is_open()))
    {
        m_outputStream << "\nINVALID FILENAME\n";
        return;
    }

    string scriptLine;

    m_outputStream << "\n";
    while (getline(file, scriptLine))
    {
        m_outputStream << scriptLine << "   ---   ";

        auto* scriptHandler = m_scriptFactory.create(scriptLine, m_ssdHelper);

        if (scriptHandler == nullptr)
        {
            m_outputStream << "\nINVALID SCRIPT\n";
            return;
        }

        m_outputStream << "Run...";

        if (false == scriptHandler->doScript())
        {
            m_outputStream << "FAIL\n";
            delete scriptHandler;
            break;
        }

        m_outputStream << "Pass\n";
        delete scriptHandler;
    }
    m_outputStream << "\n";

    file.close();
}

void Shell::parseArguments(istream& inputStream, vector<string>& args)
{
    string userInput;
    getline(inputStream, userInput);
    stringstream ss(userInput);
    string argument;
    while (getline(ss, argument, ' '))
    {
        args.push_back(argument);
    }
}

string Shell::getDirectoryPath(string filePath)
{
    size_t lastSlashPos = filePath.find_last_of('/\\');
    string dirPath = filePath;
    if (lastSlashPos != std::string::npos)
    {
        dirPath = (filePath.substr(0, lastSlashPos) + "./");
    }
    return dirPath;
}