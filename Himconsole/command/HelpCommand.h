// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
		: Command("ÏÔÊ¾ÃüÁî°ïÖúÐÅÏ¢", "Herobrine")
	{
		syntax.insert({"command", Syntax(Syntax::Type::STRING, "ÒªÏÔÊ¾°ïÖúÐÅÏ¢µÄÃüÁî", true)});
	}

	void excute(Console& console) override
	{
		if(console.getArgSize() == 0)
		{
			auto& cmds = console.getCommand();
			for(auto& cmd : cmds)
				printf("%-15s %s\n", cmd.first.c_str(), cmd.second->getDescription().c_str());
		} else {
			auto name = console.getStringArg("command");
			auto cmd	= console.getCommand(name);
			if(cmd == nullptr)
				throw "Î´ÕÒµ½ÃüÁî";
			printf("%s\n\n%s\n", cmd->getDescription().c_str(), name.c_str());
		}
	}
};


