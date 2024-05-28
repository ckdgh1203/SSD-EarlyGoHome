#pragma once

#include "SsdHelper.h"
#include "CommandHandler.cpp"
#include "CommandFactory.cpp"
#include "ScriptHandler.cpp"
#include "ScriptFactory.cpp"
#include "Exit.cpp"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Shell
{
public:

    Shell(SsdHelper& _ssd, ostream& _out) :
        m_ssdHelper(_ssd),
        m_commandFactory(_out, _ssd),
        m_outputStream(_out)
    {
    }

    void run(istream& inputStream)
    {
        while (true)
        {
            m_outputStream << "shell> ";

            vector<string> args{};
            parseArguments(inputStream, args);

            auto* scriptHandler = m_scriptFactory.create(args[0], m_commandFactory);
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

    void parseArguments(istream& inputStream, vector<string>& args)
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

private:
    ostream& m_outputStream;
    SsdHelper& m_ssdHelper;
    CommandFactory m_commandFactory;
    ScriptFactory m_scriptFactory;

    bool verifyLba(unsigned int lba)
    {
        return 99 < lba;
    }
};