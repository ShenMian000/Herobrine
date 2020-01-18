// Copyright 2019 SMS
// License(Apache-2.0)
// 自动完成

#include "AutoComplete.h"
#include "../attribute.h"

using std::string;



AutoComplete::AutoComplete(Console* console)
		: console(console), pos(0)
{
}


// 寻找匹配项
void AutoComplete::run()
{
	vector<const string*> matchs;

	switch(console->state)
	{
	case Console::State::COMMAND:
		for(auto& cmd : console->commands)
			if(console->buf == cmd.first.substr(0, console->buf.size()))
				matchs.push_back(&cmd.first);
		break;

	case Console::State::KEY:
		for(auto& cmd : console->pCommand->getSyntax())
			if(console->buf == cmd.first.substr(0, console->buf.size()))
				matchs.push_back(&cmd.first);
		break;
	}

	if(matchs.size() == 0)
	{
		cleanPrompt();
		match = nullptr;
		return;
	}
	auto newMatch = matchs.back();
	if(newMatch != match)
	{
		cleanPrompt();
		match = newMatch;
	}
	if(matchs.size() > 1)
	{
		matchs.pop_back();
		pos				= 0;
		bool flag = false;
		for(auto i = console->buf.size();; i++)
		{
			for(auto cmd : matchs)
				if(cmd->size() <= i - 1 || (*cmd)[i] != (*match)[i])
				{
					pos	 = i - console->buf.size();
					flag = true;
					break;
				}
			if(flag)
				break;
		}
	}
	else
		pos = match->size() - console->buf.size();
	printPrompt();
}


// 输出补全提示
void AutoComplete::printPrompt()
{
	Attribute::set(Attribute::fore::gray);
	printf("%s", match->substr(console->buf.size(), pos).c_str());
	for(size_t i = 0; i < pos; i++)
		printf("\b");
	Attribute::rest();
}

// 清除补全提示
void AutoComplete::cleanPrompt()
{
	for(size_t i = 0; i <= pos; i++)
		printf(" ");
	for(size_t i = 0; i <= pos; i++)
		printf("\b \b");
}


// 补全
void AutoComplete::complete()
{
	if(match == nullptr)
		return;
	printf("%s", match->substr(console->buf.size(), pos).c_str());
	console->buf += match->substr(console->buf.size(), pos);
}


