// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

#include "console.h"
#include "localization.h"
#include <ctype.h>

#ifdef OS_WIN
	#include <conio.h>
#endif



Console::Console()
{
	history.resize(historySize);
}


Console::~Console()
{
}


size_t Console::getArgSize()
{
	return args.size();
}


const string& Console::getStringArg(const string& key)
{
	return args.at(key);
}

int Console::getIntArg(const string& key)
{
	return stoi(args.at(key));
}

long Console::getLongArg(const string& key)
{
	return stol(args.at(key));
}


void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}


void Console::setHistorySize(size_t size)
{
	historySize = size;
	history.resize(historySize);
}

const string& Console::getHistory(size_t id)
{
	return history.at(id);
}

size_t Console::getHistorySize()
{
	return history.size();
}


void Console::addCommand(const string& name, Command* cmd)
{
	commands.insert({name, cmd});
}


Command* Console::getCommand(const string& name)
{
	auto res = commands.find(name);
	if(res == commands.end())
		return nullptr;
	return res->second;
}


size_t Console::getCommandSize()
{
	return commands.size();
}



void Console::console()
{
	string buffer;
	size_t pos = 0;

	string key, value;

	Syntax::Type type;

	Command* cmd;

	while(true)
	{

		bool inputValue	 = false; // 正在输入值
		bool inputString = false; // 正在输入字符串

		PrintPrompt();

		while(true)
		{
			char ch = _getch();

			if(inputValue)
			{
				// 输入 值
				switch(cmd->syntax[key].type)
				{
				case Syntax::Type::INT:
				case Syntax::Type::LONG:
					break;

				case Syntax::Type::FLOAT:
				case Syntax::Type::DOUBLE:
					break;

				case Syntax::Type::STRING:
					break;

				case Syntax::Type::OPTION:
					break;
				}
			}
			else
			{
				// 输入 键
				if(!isalnum(ch) || ch != 95)
					continue;

				if(ch == 95)
					inputValue = true;
				else
					key += ch;
			}

			printf("%c", ch);

			if(ch == '\r')
				break;

			buffer += ch;
		}

		try
		{
			cmd->excute(*this);
		} catch(char* error)
		{
			print::error(error);
		}
	}
}


/*
		case ' ':
			if(inputString)
				break;
		case '\r':
			if(inputValue)
			{
				value = buffer.substr(pos);
				if()
					arg.Long = stol(value);
				else
					arg.String = value;
			}
			break;

		case '"':
			if(!inputValue)
				continue;

			if(!inputString)
			{
				// 检查key对应的类型是不是string
				inputString = true;
			}
			else
			{
				arg.String = buffer.substr(pos);
				args.insert({key, arg});
				inputString = false;
			}
			break;

		case ':':
			key				 = buffer.substr(pos);
			pos				 = buffer.size();
			inputValue = true;
			break;
*/


// 输出命令行提示符
void Console::PrintPrompt()
{
	printf("\n");
	Attribute::set(Attribute::mode::underline);
	printf(prompt.c_str());
	Attribute::rest();
	printf("> ");
}


// 读入一个字符, 不回显
inline int Console::GetChar()
{
#ifdef OS_WIN
	return _getch();
#endif

#ifdef OS_LINUX
	system("stty -echo");
	system("stty -icanon");
	char c = getchar();
	system("stty icanon");
	system("stty echo");
	return c;
#endif
}
