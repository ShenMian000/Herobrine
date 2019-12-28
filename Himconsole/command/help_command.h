// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
		: Command("help", "œ‘ æ√¸¡Ó∞Ô÷˙–≈œ¢", "Herobrine")
	{
	}

	void excute(Console& console) override
	{
		auto size = console.getCommandSize();

		for(size_t i = 0; i < size; i++)
		{
			auto cmd = console.getCommand(i);

			printf("%-15s %s\n", cmd->getName().c_str(), cmd->getDescription().c_str());
		}
	}
};


