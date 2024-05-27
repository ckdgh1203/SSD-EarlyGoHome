#include "Command.cpp"


class CommandFactory
{
public:
	static CommandFactory& getInstance()
	{
		static CommandFactory instance{};
		return instance;
	}

	Command* createCommand(int lba)
	{
		return new ReadCommand{lba };
	}
	Command* createCommand(int lba, string data)
	{
		return new WriteCommand{lba, data };
	}
	Command* createCommand(int lba, int size)
	{
		return new EraseCommand{lba, size };
	}

private:
	CommandFactory() {}
	CommandFactory& operator=(const CommandFactory& other) = delete;
	CommandFactory(const CommandFactory& other) = delete;
};