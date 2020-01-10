// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
			: Command("显示命令帮助信息", "Herobrine")
	{
		syntax.insert({"command", Syntax(Syntax::Type::STRING, "要显示帮助信息的命令", true)});
	}

	void excute(Console& console) override
	{
		if(console.getArgSize() == 0)
		{
			auto& cmds = console.getCommand();
			for(auto& cmd : cmds)
				printf("%-15s %s\n", cmd.first.c_str(), cmd.second->getDescription().c_str());
		}
		else
		{
			auto name = console.getStringArg("command");
			auto cmd	= console.getCommand(name);
			if(cmd == nullptr)
				throw "未找到命令";
			printf("描述:\n\t%s\n\n", cmd->getDescription().c_str());
			printf("作者:\n\t%s\n\n", cmd->getAuthor().c_str());
			printf("开源协议:\n\t");
			switch(cmd->getLicense())
			{
			case License::Apache_2_0:
				printf("Apache 2.0");
				break;

			case License::TIM:
				printf("TIM");
				break;
			}
		}
	}
};
