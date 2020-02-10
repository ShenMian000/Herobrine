// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

#include "himconsole.h"
#include "Server.h"
#include "localization.h"

#include "console/command/ClearCommand.h"
#include "console/command/ExecCommand.h"
#include "console/command/HelpCommand.h"
#include "console/command/HistoryCommand.h"



Himconsole::Himconsole()
{
}

Himconsole::~Himconsole()
{
}



///////////
/*
class ListenCommand : public Command
{
public:
	ListenCommand()
			: Command("监听指定地址和端口", "[TEST]", Platform::Common, License::Apache_2_0)
	{
		addSyntax("ip",   {Syntax::Type::STRING, "监听地址", false});
		addSyntax("port", {Syntax::Type::INT, "监听端口", false});
	}

	void excute(Console& console) override
	{
	}
};
*/

int main()
{
	print::warn(local::WARN_DEBUG);
	printf(
			"  __      __    __\n"
			" |  |    |  |  |__|   __________\n"
			" |  |____|  |   __   |  __  __  |\n"
			" |   ____   |  |  |  |  ||  ||  |\n"
			" |  |    |  |  |  |  |  ||  ||  |\n"
			" |__|    |__|  |__|  |__||__||__|\n"
			"\n"
			" [Herobrine (Alpha)             ]\n"
			" [Update Date: %-17.17s]\n"
			" [Update Time: %-17.17s]\n",
			__DATE__, __TIME__);

	Console console;
	Server	server(25565);

	console.setPrompt("him");

	console.addCommand("clear",   dynamic_cast<Command*>(new ClearCommand()));
	console.addCommand("exec",    dynamic_cast<Command*>(new ExecCommand()));
	console.addCommand("help",    dynamic_cast<Command*>(new HelpCommand()));
	console.addCommand("history", dynamic_cast<Command*>(new HistoryCommand()));

	server.run();
	console.run();

	return 0;
}
///////////


