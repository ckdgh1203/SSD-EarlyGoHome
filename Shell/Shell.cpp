#include "Shell.h"

void Shell::run(istream& inputStream)
{
    while (true)
    {
        m_outputStream << "shell> ";

        vector<string> args{};
        parseArguments(inputStream, args);

        auto* scriptHandler = m_scriptFactory.create(args[0], m_ssdHelper);
        if (scriptHandler != nullptr)
        {
            scriptHandler->doScript();
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
