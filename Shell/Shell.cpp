#include "SsdExcutable.h"
#include "SsdResult.h"
#include "Exit.h"

#include <iostream>
#include <sstream>
#include <vector>

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
        m_outputStream << m_helpMessage;
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
        while (true)
        {
            m_outputStream << "shell> ";

            vector<string> args{};
            parseArguments(inputStream, args);

            if (args[0] == "exit")
            {
                exit();
                return;
            }

            if (args[0] == "read")
            {
                read(stoi(args[1]));
            }
            else if (args[0] == "write")
            {
                write(stoi(args[1]), args[2]);
            }
            else if (args[0] == "fullread")
            {
                fullread();
            }
            else if (args[0] == "fullwrite")
            {
                fullwrite(args[1]);
            }
            else if (args[0] == "help")
            {
                help();
            }
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

    void read(unsigned int lba)
    {
        if (verifyLba(lba))
        {
            m_outputStream << "Out of Lba";
            return;
        }
        string arguments = "R " + to_string(lba);
        m_ssdExcutable->execute(arguments);
        m_outputStream << m_ssdResult->get() << endl;
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

	void doTestApp1()
	{
		fullwrite("0xDEADC0DE");
		fullread();

		bool isCompareSuccess = readCompare("0xDEADC0DE", 100);

		if (false == isCompareSuccess)
		{
			m_outputStream << "[WARNING] testapp1 : written data is different with read data!!!" << endl;
			return;
		}

		m_outputStream << "testapp1 : Done test, written data is same with read data :)" << endl;
	}

    void doTestApp2()
    {
        unsigned int lbaBound = 6;

        for (int i = 0; i < 30; i++)
        {
            writeRepeatedly("0xAAAABBBB", lbaBound);
        }

        writeRepeatedly("0x12345678", lbaBound);
        readRepeatedly(lbaBound);

        bool isCompareSuccess = readCompare("0x12345678", lbaBound);

        if (false == isCompareSuccess)
        {
            m_outputStream << "[WARNING] testapp2 : written data is different with read data!!!" << endl;
            return;
        }
        m_outputStream << "testapp2 : Done test, written data is same with read data :)" << endl;
    }

protected:
    const string m_helpMessage = "Help:\n"
        "\tread [LBA]\n"
        "\twrite [LBA] [DATA]\n"
        "\tfullread\n"
        "\tfullwrite [DATA]\n";

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

    bool readCompare(const string& inputData, unsigned int lbaBound)
    {
        string referenceData = "";
        for (int iter = 0; iter < lbaBound; iter++)
        {
            referenceData += inputData + "\n";
        }

        ostringstream* redirectedOutput = dynamic_cast<ostringstream*>(&m_outputStream);
        string readData = redirectedOutput->str();
        redirectedOutput->str("");
        redirectedOutput->clear();

        return (referenceData == readData);
    }

    void readRepeatedly(const int lbaBound)
    {
        for (int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            read(lbaIter);
        }
    }

    void writeRepeatedly(const string& inputData, const int lbaBound)
    {
        for (int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            write(lbaIter, inputData);
        }
    }
};