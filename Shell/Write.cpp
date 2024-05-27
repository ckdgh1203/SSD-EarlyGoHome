#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Write : public CommandHandler
{
public:
	Write(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	// write 123 0x12345678
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 3)
			return INVALID;
		unsigned long test = stoul(args[1]);

		if (stoi(args[1]) < 0 || stoi(args[1]) > 99)
			return INVALID;

		if (args[2].size() != 10)
			return INVALID;

		if (args[2][0] != '0' || args[2][1] != 'x')
			return INVALID;

		for (int i = 2; i < 10; i++)
		{
			if (!isxdigit(args[2][i]))
				return INVALID;
		}

		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		string arguments = "W " + args[1] + " " + args[2] + "\n";
		m_ssdHelper.execute(arguments);
		return Progress::Continue;
	}

	void usage() override {};

	~Write() {};
private:

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