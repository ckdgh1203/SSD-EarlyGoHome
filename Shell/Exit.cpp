#pragma once

#include "Exit.h"

bool Exit::isValidArgs(const vector<string>& args)
{
    if (args.size() != 1)
        return INVALID;

    return VALID;
}

Progress Exit::doCommand(const vector<string>& args)
{
    m_outputStream << "Exit from Shell" << endl;
    logger.print("Command : " + sliceString(args, 0));
    return Progress::Done;
}
