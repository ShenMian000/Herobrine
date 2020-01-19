// Copyright 2019 SMS
// License(Apache-2.0)
// 自动完成

#include "../include.h"
#include "Console.h"

#ifndef AUTO_COMPLETE_H_
#define AUTO_COMPLETE_H_



class AutoComplete
{
public:
	explicit AutoComplete(Console*);
	
	void run();

	void complete();

private:
	Console*							console;
	const std::string*		matched = nullptr;
	vector<const string*> matchs;
	size_t								pos;

	void PrintPrompt();
	void CleanPrompt();

	void MatchCommand(const string& cmd);
	void MatchArgument(const string& arg);
};



#endif // AUTO_COMPLETE_H_
