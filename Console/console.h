// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>
#include <map>
#include "console_input.h"

class Console
{
public:
	void inputLine();

	void setCommand(const std::string&);
	void addParameter(const std::string&, const std::string&);

private:
	std::map<std::string, std::string> parameters;
	ConsoleInput input;
};

#endif // CONSOLE_H_

