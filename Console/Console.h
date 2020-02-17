// Copyright 2019 SMS
// License(Apache-2.0)

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>
#include <map>
class Command;



class Console
{
public:
	static Console& getInstance();

	void run();

	void addCommand(const std::string&, Command*);

	void setPrompt(const std::string&);
	
private:
	Console();
	static Console*										 instance;
	std::string												 prompt;
	std::map<std::string, std::string> args;
	std::map<std::string, Command*>		 commands;
};



#endif // CONSOLE_H_
