// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
		: Command("help", "œ‘ æ√¸¡Ó∞Ô÷˙–≈œ¢", "Herobrine")
	{
		syntax.push_back({"command", Argument::Type::String});
	}

	void excute(Console& console) override
	{
		if(console.getArgSize() == 0)
		{
			auto size = console.getCommandSize();
			for(size_t i = 0; i < size; i++)
			{
				auto cmd = console.getCommand(i);
				printf("%-15s %s\n", cmd->getName().c_str(), cmd->getDescription().c_str());
			}
		} else {
			string name = console.getStringArg("command");
			auto   cmd  = console.getCommand(name);
			printf("%-15s %s\n", cmd->getName().c_str(), cmd->getDescription().c_str());
		}
	}
};


