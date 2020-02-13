// Copyright 2019 SMS
// License(Apache-2.0)
// √¸¡Ó––

#include "himconsole.h"
#include "Server.h"
#include "localization.h"

#include "console/command/ClearCommand.h"
#include "console/command/ExecCommand.h"
#include "console/command/HelpCommand.h"
#include "console/command/HistoryCommand.h"
#include "command/ListenCommand.h"



Himconsole::Himconsole()
{
}

Himconsole::~Himconsole()
{
}



///////////

int main()
{
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

	console.setPrompt("him");

	console.addCommand("clear",   dynamic_cast<Command*>(new ClearCommand()));
	console.addCommand("exec",    dynamic_cast<Command*>(new ExecCommand()));
	console.addCommand("help",    dynamic_cast<Command*>(new HelpCommand()));
	console.addCommand("history", dynamic_cast<Command*>(new HistoryCommand()));
	console.addCommand("listen",  dynamic_cast<Command*>(new ListenCommand()));

	console.run();

	return 0;
}
///////////


