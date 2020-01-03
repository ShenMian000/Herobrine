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
	if(getCommand(name) != nullptr)
		; // TODO

	commands.insert({name, cmd});
}


Command* Console::getCommand(const string& name)
{
	auto res = commands.find(name);
	if(res == commands.end())
		return nullptr;
	return res->second;
}


const map<string, Command*>& Console::getCommand()
{
	return commands;
}



enum class InputState
{
	CMD, // 输入命令
	KEY, // 输入键
	ARG	 // 输入值
};

void Console::run()
{
	InputState inputState = InputState::CMD;

	while(true)
	{
		string buf;

		PrintPrompt();

		while(true)
		{
			char ch = GetChar();

			switch(inputState)
			{
			case InputState::CMD:
				break;

			case InputState::KEY:
				break;

			case InputState::ARG:
				break;
			}

			buf += ch;
		}

		buf.clear();
	}
}



void Console::console()
{
	string key, value;

	while(true)
	{
		Syntax*	 syntax = nullptr;
		Command* cmd		= nullptr;
		string*	 arg		= nullptr;

		size_t				 cPos = 0; // 当前光标位置
		vector<size_t> lPos;		 // 命令/参数结尾

		size_t keySize = 0;

		bool inputValue	 = false; // 正在输入值
		bool inputString = false; // 正在输入字符串

		PrintPrompt();

		// 输入 命令
		// TODO(SMS): 此处是否要使用goto语句简化流程
		while(true)
		{
			string buf;

			char ch = GetChar();

			if(!isprint(ch))
			{
				printf("\a");
				continue;
			}

			if(ch == ' ' || ch == '\r')
			{
				cmd = getCommand(buf);
				if(cmd == nullptr)
				{
					printf("\a");
					continue;
				}
				break;
			}

			buf += ch;
		}

		while(true)
		{
			char ch = GetChar();

			if(inputValue)
			{
				// 输入 值
				if(arg == nullptr)
					arg = &args[key];

				if(ch == '\r' || (inputString == false && ch == ' '))
				{
					inputValue = false;
					key.clear();
					break;
				}

				switch(cmd->syntax[key].type)
				{
				case Syntax::Type::INT:
			case Syntax::Type::LONG:
				if(!isalnum(ch))
				{
					printf("\a");
					continue;
				}
				break;

			case Syntax::Type::FLOAT:
			case Syntax::Type::DOUBLE:
				if(!isalnum(ch) && ch != '.')
				{
					printf("\a");
					continue;
				}
				break;

			case Syntax::Type::STRING:
				if(!isprint(ch))
				{
					printf("\a");
					continue;
				}
				if(ch == '"')
					if(!inputString)
						inputString = true;
					else
						inputString = false;
				break;

			case Syntax::Type::OPTION:
				if(!isalnum(ch) && ch != '_')
				{
					printf("\a");
					continue;
				}
				break;
			}

			if(ch == '"')
				break;

			arg += ch;
		}
		else
		{
			// 输入 键
		}

		if(ch == '\r')
		{
			printf("\n");
			break;
		}

		printf("%c", ch);
		cPos++;
	}

	args.clear();

	assert(cmd != nullptr);

	try
	{
		cmd->excute(*this);
	}
	catch(char* error)
	{
		print::error(error);
	}
}
}


/*

				if(!isalnum(ch) && ch != ' ' && ch != '_' && ch != '\r' && ch != '\b')
				{
					printf("\a");
					continue;
				}

				if(cmd == nullptr || ch == ' ' || ch == '\r')
				{
					cmd = getCommand(key);
					if(cmd == nullptr)
					{
						if(key == "exit")
							return;

						printf("\a");
						continue;
					}
				}

				switch(ch)
				{
				case ' ':
					// 是否连续输入两个空格
					if(key.size() == 0)
					{
						printf("\a");
						continue;
					}

					// 是否可以继续填写参数
					if(cmd->syntax.size() <= args.size())
					{
						printf("\a");
						continue;
					}

					lPos.push_back(cPos);
					inputValue = true;
					arg = nullptr;
					break;

				case '\r':
					// 是否可以不填写任何参数(必填参数全部填写完毕)
					if(cmd->syntax.size() != 0)
						for(auto& s : cmd->syntax)
							if(s.second.required == false)
							{
								printf("\a");
								continue;
							}
					
					lPos.push_back(cPos);
					inputValue = true;
					break;

				case '\b':
					if(cPos > 0)
					{
						cPos--;
						printf("\b \b");

						// 回到上一个参数
						if(cPos == lPos.back())
						{
							cPos = lPos.back();
							key  = 
							lPos.pop_back();
							inputValue = true;
							arg = nullptr;
							continue;
						}

						key.pop_back();
					} else
					{
						printf("\a");
						continue;
					}

				default:
					key += ch;
				}
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
