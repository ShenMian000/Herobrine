// Copyright 2019 SMS
// License(Apache-2.0)
// 自动完成

#include "../include.h"

#ifndef AUTO_COMPLETE_H_
#define AUTO_COMPLETE_H_



class Console;
class Command;
enum class State;

class AutoComplete
{
public:
	AutoComplete(Console*);

	void run(State, const string&, const Command*);
	void complete(string&);

private:
	size_t								pos		= 0;
	const std::string*		match = nullptr;
	vector<const string*> matchs;
	Console&							console;

	void PrintPrompt(const string&);
	void CleanPrompt();

	void MatchCommand(const string&);
	void MatchArgument(const Command*, const string&);
};



#endif // AUTO_COMPLETE_H_
