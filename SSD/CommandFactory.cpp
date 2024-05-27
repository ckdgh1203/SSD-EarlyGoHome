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
	Command* createCommand(iFile* file, int lba, int size)
	{
		return new EraseCommand{file, lba, size };
	}

private:
	CommandFactory() {}
	CommandFactory& operator=(const CommandFactory& other) = delete;
	CommandFactory(const CommandFactory& other) = delete;
};