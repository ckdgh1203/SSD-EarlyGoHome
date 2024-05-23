#include "SsdExcutable.h"
#include "SsdResult.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class iExit
{
public:
    virtual void doExit() = 0;
private:
};

class Exit : public iExit
{
public:
    void doExit() override
    {
        exit(0);
    }
private:
};

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
        while (true)
        {
            m_outputStream << "\nshell> ";

            getline(inputStream, userInput);
            stringstream ss(userInput);
            string argument;
            vector<string> args{};
            while (getline(ss, argument, ' '))
            {
                args.push_back(argument);
            }

            m_outputStream << userInput << endl;
            if (args[0] == "exit")
            {
                exit();
                return;
            }

            if (args[0] == "read")
            {
                read(stoi(args[1]));
            }
            else if (userInput.find("write") == 0)
            {
                write(stoi(args[1]), args[2]);
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
        string arguments = "R " + to_string(lba) + "\n";
        m_ssdExcutable->execute(arguments);
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