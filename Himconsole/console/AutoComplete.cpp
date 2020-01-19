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


void AutoComplete::run()
{
	switch(console->state)
	{
	case Console::State::COMMAND:
		MatchCommand(console->buf);
		break;

	case Console::State::KEY:
		MatchArgument(console->buf);
		break;

	default:
		return;
	}

	if(matchs.size() == 0)
	{
		CleanPrompt();
		matched = nullptr;
		return;
	}
	auto newMatch = matchs.back();
	if(newMatch != matched)
	{
		CleanPrompt();
		matched = newMatch;
	}
	if(matchs.size() > 1)
	{
		matchs.pop_back();
		pos				= 0;
		bool flag = false;
		for(auto i = console->buf.size();; i++)
		{
			for(auto cmd : matchs)
				if(cmd->size() <= i - 1 || (*cmd)[i] != (*matched)[i])
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
		pos = matched->size() - console->buf.size();
	PrintPrompt();
}


// 输出补全提示
void AutoComplete::PrintPrompt()
{
	Attribute::set(Attribute::Fore::gray);
	printf("%s", matched->substr(console->buf.size(), pos).c_str());
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
void AutoComplete::MatchCommand(const string& cmd)
{
	matchs.clear();

	for(auto& i : console->commands)
		if(cmd == i.first.substr(0, cmd.size()))
			matchs.push_back(&i.first);
}

// 查找参数匹配项
void AutoComplete::MatchArgument(const string& arg)
{
	matchs.clear();

	for(auto& syntax : console->pCommand->getSyntax())
		if(!console->isFilled(&syntax.second) && arg == syntax.first.substr(0, arg.size()))
			matchs.push_back(&syntax.first);
}


// 补全
void AutoComplete::complete()
{
	if(matched == nullptr)
		return;
	printf("%s", matched->substr(console->buf.size(), pos).c_str());
	console->buf += matched->substr(console->buf.size(), pos);
	return;
}
