#pragma once
#include <string>
#include <iostream>

class DataFormatVerifier
{
public:
    DataFormatVerifier(std::ostream& _out) : m_outputStream(_out) {}
    bool isInvalidDataFormat(const std::string& data)
    {
        if (isInvalidLengthOfData(data)) return true;
        if (isInvalidPrefix(data)) return true;
        if (hasInvalidCharater(data)) return true;
        return false;
    }
private:
    std::ostream& m_outputStream;
    bool isInvalidLengthOfData(const std::string& data)
    {
        if (data.size() != 10)
        {
            m_outputStream << "[WARNING] Invalid input data length !!!" << std::endl;
            return true;
        }
        return false;
    }

    bool isInvalidPrefix(const std::string& data)
    {
        if (data[0] != '0' || data[1] != 'x')
        {
            m_outputStream << "[WARNING] Prefix '0x' was not included in input data !!!" << std::endl;
            return true;
        }
        return false;
    }

    bool hasInvalidCharater(const std::string& data)
    {
        for (int index = 2; index < data.length(); index++)
        {
            if (('A' <= data[index] && data[index] <= 'F') || ('0' <= data[index] && data[index] <= '9'))
            {
                continue;
            }

            m_outputStream << "[WARNING] Input data has invalid characters !!!" << std::endl;
            return true;
        }

        return false;
    }

};