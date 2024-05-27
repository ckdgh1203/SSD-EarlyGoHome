#include "Command.cpp"


class CommandFactory
{
public:
	static CommandFactory& getInstance()
	{
		static CommandFactory instance{};
		return instance;
	}
	Command* createCommand(iFile* file, int lba)
	{
		return new ReadCommand{file, lba};
	}
	Command* createCommand(iFile* file, int lba, string data)
	{
		return new WriteCommand{file, lba, data };
	}

private:
	CommandFactory() {}
	CommandFactory& operator=(const CommandFactory& other) = delete;
	CommandFactory(const CommandFactory& other) = delete;
};