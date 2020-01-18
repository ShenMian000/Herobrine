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

	void printPrompt();
	void cleanPrompt();

	bool complete();

private:
	Console*					 console;
	const std::string* match = nullptr;
	size_t						 pos;
};



#endif // AUTO_COMPLETE_H_
