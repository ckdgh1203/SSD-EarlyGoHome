#pragma once

#include <string>
#include <iostream>

using namespace std;

class Logger
{
public:
	Logger() 
	{
		latest = new FILE();
	};

	void print(string msg)
	{
		cout << "Hello : " << msg << endl;
		//cout << __PRETTY_FUNCTION__ << endl;
	}

	void getNextFile()
	{
		cout << "Get Next File " << endl;
	}

	void zip()
	{
		cout << "Zip " << endl;
	}
	~Logger() 
	{
		if (latest)
			fclose(latest);
	};
private:
	FILE* latest;
};