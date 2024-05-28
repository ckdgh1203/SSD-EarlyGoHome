#pragma once

#include <string>

using namespace std;

class ISsdResult
{
public:
    virtual string get(void) = 0;
    virtual void setResultFilePath(string) = 0;
};

class SsdResult : public ISsdResult
{
public:
    string get(void) override
    {
        if (resultFilePath.empty())
            return std::string();

        ifstream file(resultFilePath);
        if (!file.is_open())
            return std::string();

        string buf;
        while (getline(file, buf))
            cout << buf << endl;

        file.close();

        return buf;
    }

    void setResultFilePath(string path)
    {
        resultFilePath = path;
    }
private:
    string resultFilePath;
};
