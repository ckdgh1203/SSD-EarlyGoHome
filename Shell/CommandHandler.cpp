#include "CommandHandler.h"

inline string CommandHandler::sliceString(const vector<string>& words, size_t start)
{
	string result;
	for (size_t i = start; i < words.size(); ++i)
	{
		result += words[i];
		if (i != words.size() - 1)
		{
			result += " ";
		}
	}
	return result;
}
