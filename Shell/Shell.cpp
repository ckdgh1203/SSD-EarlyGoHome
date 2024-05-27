#pragma once

#include "SsdHelper.h"
#include "CommandHandler.cpp"
#include "CommandFactory.cpp"
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

            auto* commandHandler = m_commandFactory.create(args[0]);
            if (commandHandler == nullptr)
            {
                m_outputStream << "\nINVALID COMMAND";
                continue;
            }

            if (!commandHandler->isValidArgs(args))
            {
                m_outputStream << "\nINVALID COMMAND";
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

	void doTestApp1()
	{
		//fullwrite("0xDEADC0DE");
		//fullread();

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

private:
    ostream& m_outputStream;
    SsdHelper& m_ssdHelper;
    CommandFactory m_commandFactory;

    bool verifyLba(unsigned int lba)
    {
        return 99 < lba;
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
            //read(lbaIter);
        }
    }

    void writeRepeatedly(const string& inputData, const int lbaBound)
    {
        for (int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            //write(lbaIter, inputData);
        }
    }
};