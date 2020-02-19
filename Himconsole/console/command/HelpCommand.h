// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
			: Command("显示命令帮助信息", "Herobrine", Platform::Common, License::Apache_2_0)
	{
		addSyntax("command", {Syntax::Type::STRING, "要显示帮助信息的命令", true});
	}

	void excute(Console& c) override
	{
		if(c.getArgSize() == 0)
		{
			auto& cmds = c.getCommand();
			for(auto& cmd : cmds)
				printf("%-15s %s\n", cmd.first.c_str(), cmd.second->getDescription().c_str());
		}
		else
		{
			auto name = c.getStringArg("command");
			auto cmd	= c.getCommand(name);
			if(cmd == nullptr)
				throw "未找到命令";
			printf("描述:\n  %s\n\n", cmd->getDescription().c_str());
			printf("语法:\n");
			for(auto& syntax : cmd->getSyntax())
			{
				switch(syntax.second.type)
				{
				case Syntax::Type::INT:
				case Syntax::Type::LONG:
				case Syntax::Type::FLOAT:
				case Syntax::Type::DOUBLE:
					attribute::set(attribute::fore::blue);
					attribute::set(attribute::mode::fore_bold);
					break;

				case Syntax::Type::STRING:
					attribute::set(attribute::fore::yellow);
					attribute::set(attribute::mode::fore_bold);
					break;

				case Syntax::Type::OPTION:
					attribute::set(attribute::fore::white);
					attribute::set(attribute::mode::fore_bold);
					break;
				}
				if(syntax.second.required)
					printf("  %-15s ", syntax.first.c_str());
				else
					printf("  %-15s ", (syntax.first + '*').c_str());
				attribute::rest();
				printf("%-30s\n", syntax.second.desc.c_str());
			}
			printf("\n");
			printf("作者:\n  %s\n\n", cmd->getAuthor().c_str());
			printf("开源协议:\n  ");
			switch(cmd->getLicense())
			{
			case License::Apache_2_0:
					puts("Apache 2.0 http://www.apache.org/licenses/LICENSE-2.0");
					break;

				case License::TIM:
					puts("TIM http://www.opensource.org/licenses/mit-license.php");
					break;

				case License::GPL_3_0:
					puts("GPL 3.0 https://www.gnu.org/licenses/gpl-3.0.en.html");
					break;

				case License::LGPL_3_0:
					puts("LGPL 3.0 https://opensource.org/licenses/LGPL-3.0");
					break;

				case License::BSD_2_Clause:
					puts("BSD 2-Clause https://opensource.org/licenses/BSD-2-Clause");
					break;

				case License::BSD_3_Clause:
					puts("BSD 3-Clause https://opensource.org/licenses/BSD-3-Clause");
					break;

				case License::MPL_2_0:
					puts("MPL 2.0 https://opensource.org/licenses/MPL-2.0");
					break;
				}
			}
		}
	};
