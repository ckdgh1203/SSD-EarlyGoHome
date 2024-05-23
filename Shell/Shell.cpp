#pragma once

#include "SsdExcutable.h"
#include "SsdResult.h"
#include "CommandHandler.cpp"
#include "Exit.cpp"

#include <iostream>
#include <sstream>
#include "CommandFactory.cpp"

using namespace std;

class Shell
{
public:

    Shell(void) : m_outputStream(cout)
    {
        _exit = new Exit();
    }

    Shell(ISsdExecutable* executable, ISsdResult* result, ostream& _out) :
        m_ssdExcutable(executable), m_ssdResult(result),
        m_outputStream(_out)
    {
        _exit = new Exit();
    }

    void help()
    {
        helpMessasge();
    }

    void helpMessasge()
    {
        m_outputStream << "This is Help Message" << endl;
    }

    void exit()
    { 
        _exit->doExit();
    }

    void setExit(iExit *newExit)
    {
        _exit = newExit;
    }

    void run(istream& inputStream)
    {
        string userInput;
        CommandFactory commandFactory;
        CommandHandler *commandHandler;

        while (true)
        {
            m_outputStream << "\nshelasdl> ";
            getline(inputStream, userInput);
            m_outputStream << userInput << endl;
            if (userInput.find("read") == 0)
            {
                commandHandler = commandFactory.create("read");
            }
            if (userInput.find("write") == 0)
            {
                commandHandler = commandFactory.create("write");
            }
            if (userInput.find("fullread") == 0)
            {
                commandHandler = commandFactory.create("fullread");
            }
            if (userInput.find("fullwrite") == 0)
            {
                commandHandler = commandFactory.create("fullwrite");
            }
            if (userInput == "help")
            {
                commandHandler = commandFactory.create("help");
            }
            if (userInput == "exit") 
            {
                commandHandler = commandFactory.create("exit");
            }

        }
    }

    void read(unsigned int lba)
    {
        if (verifyLba(lba))
        {
            m_outputStream << "Out of Lba";
            return;
        }
        m_ssdExcutable->execute("R 3\n");
        m_outputStream << m_ssdResult->get();
    }

    void write(unsigned int lba, const string& inputData)
    {
        if (verifyLba(lba)) return;
        if (verifyDataFormat(inputData)) return;
        if (false == IsInputDataWithPrefix(inputData))	return;
        if (false == IsInputDataWithValidRange(inputData)) return;

        string arguments = "W " + to_string(lba) + " " + inputData + "\n";
        m_ssdExcutable->execute(arguments);
    }

    void fullwrite(const string& inputData)
    {
        if (false == IsInputDataWithPrefix(inputData))	return;
        if (false == IsInputDataWithValidRange(inputData)) return;
        for (int iter = 0; iter < 100; iter++)
        {
            write(iter, inputData);
        }
    }

    void fullread()
    {
        for (int iter = 0; iter < 100; iter++)
        {
            read(iter);
        }
    }

private:
    iExit* _exit;
    ISsdExecutable* m_ssdExcutable{};
    ISsdResult* m_ssdResult{};
    ostream& m_outputStream;

    bool verifyLba(unsigned int lba)
    {
        return 99 < lba;
    }

    bool verifyDataFormat(const std::string& data)
    {
        if (data.size() != 10)
        {
            m_outputStream << "[WARNING] Invalid input data length !!!" << endl;
        }
        return data.size() != 10;
    }

    bool IsInputDataWithPrefix(const std::string& inputData)
    {
        if (inputData[0] != '0' || inputData[1] != 'x')
        {
            m_outputStream << "[WARNING] Prefix '0x' was not included in input data !!!" << endl;
            return false;
        }

        return true;
    }

    bool IsInputDataWithValidRange(const std::string& inputData)
    {
        for (int index = 2; index < inputData.length(); index++)
        {
            if (('A' <= inputData[index] && inputData[index] <= 'F') || ('0' <= inputData[index] && inputData[index] <= '9'))
            {
                continue;
            }

            m_outputStream << "[WARNING] Input data has invalid characters !!!" << endl;
            return false;
        }

        return true;
    }
};