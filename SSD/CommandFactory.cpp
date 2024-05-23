#include "Command.cpp"


class CommandFactory
{
public:
	static CommandFactory& getInstance()
	{
		static CommandFactory instance{};
		return instance;
	}
	Command* createCommand(iFile* m_file, int lba)
	{
		return new ReadCommand{m_file, lba };
	}
	Command* createCommand(iFile* m_file, int lba, string data)
	{
		return new WriteCommand{m_file, lba, data };
	}

private:
	CommandFactory() {}
	CommandFactory& operator=(const CommandFactory& other) = delete;
	CommandFactory(const CommandFactory& other) = delete;
};