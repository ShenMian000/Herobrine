// Copyright 2019 SMS
// License(Apache-2.0)
// 自动完成

#include "AutoComplete.h"
#include "Console.h"
#include "Command.h"
#include "../attribute.h"

using std::string;



AutoComplete::AutoComplete(Console* console)
		: console(*console)
{
}


void AutoComplete::run(State state, const string& str, const Command* pCmd)
{
	switch(state)
	{
	case State::COMMAND:
		MatchCommand(str);
		break;

	case State::KEY:
		MatchArgument(pCmd, str);
		break;

	default:
		return;
	}

	if(matchs.size() == 0)
	{
		CleanPrompt();
		match = nullptr;
		return;
	}
	auto newMatch = matchs.back();
	if(newMatch != match)
	{
		CleanPrompt();
		match = newMatch;
	}
	if(matchs.size() > 1)
	{
		matchs.pop_back();
		pos				= 0;
		bool flag = false;
		for(auto i = str.size();; i++)
		{
			for(auto cmd : matchs)
				if(cmd->size() <= i - 1 || (*cmd)[i] != (*match)[i])
				{
					pos	 = i - str.size();
					flag = true;
					break;
				}
			if(flag)
				break;
		}
	}
	else
		pos = match->size() - str.size();
	PrintPrompt(str);

	matchs.clear();
}


// 输出补全提示
void AutoComplete::PrintPrompt(const string& str)
{
	Attribute::set(Attribute::Fore::gray);
	printf("%s", match->substr(str.size(), pos).c_str());
	for(size_t i = 0; i < pos; i++)
		printf("\b");
	Attribute::rest();
}


// 清除补全提示
void AutoComplete::CleanPrompt()
{
	for(size_t i = 0; i <= pos; i++)
		printf(" ");
	for(size_t i = 0; i <= pos; i++)
		printf("\b \b");
}


// 查找命令匹配项
void AutoComplete::MatchCommand(const string& str)
{
	for(auto& i : console.getCommand())
		if(str == i.first.substr(0, str.size()))
			matchs.push_back(&i.first);
}

// 查找参数匹配项
void AutoComplete::MatchArgument(const Command* cmd, const string& str)
{
	for(auto& syntax : cmd->getSyntax())
		if(str == syntax.first.substr(0, str.size()))
			matchs.push_back(&syntax.first);
}


// 补全
void AutoComplete::complete(string& str)
{
	if(match == nullptr)
		return;
	printf("%s", match->substr(str.size(), pos).c_str());
	str += match->substr(str.size(), pos);
	return;
}
