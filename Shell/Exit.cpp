#include "Exit.h"

bool Exit::isValidArgs(const vector<string>& args)
{
    if (args.size() != 1)
        return INVALID;

    return VALID;
}
#include <chrono>
#include <thread>
Progress Exit::doCommand(const vector<string>& args)
{
    m_outputStream << "Exit from Shell" << endl;
    logger.print("Command : " + sliceString(args, 0));
    logger.clean();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    return Progress::Done;
}
