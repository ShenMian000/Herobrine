// Copyright 2020 SMS
// License(Apache-2.0)

#include "console.h"
#include <conio.h>
#include <assert.h>

void Console::inputLine()
{
	do
	{
		char c = _getch();
		input.handle(c);
	} while(!input.isEnded());
}

void Console::setCommand(const std::string&)
{
}

void Console::addParameter(const std::string& key, const std::string& value)
{
	parameters.insert({key, value});
}
