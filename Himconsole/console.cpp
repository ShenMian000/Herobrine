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
	historys.resize(historySize);
}


Console::~Console()
{
}


size_t Console::getArgSize() const
{
	return args.size();
}


const string& Console::getStringArg(const string& key) const
{
	return args.at(key);
}

int Console::getIntArg(const string& key) const
{
	return stoi(args.at(key));
}

long Console::getLongArg(const string& key) const
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
	historys.resize(historySize);
}

const deque<string>& Console::getHistory() const
{
	return historys;
}


void Console::addCommand(const string& name, Command* cmd)
{
	if(getCommand(name) != nullptr)
		; // TODO

	commands.insert({name, cmd});
}


void Console::delCommand(const string& name)
{
	commands.erase(name);
}


Command* Console::getCommand(const string& name) const
{
	auto res = commands.find(name);
	if(res == commands.end())
		return nullptr;
	return res->second;
}


Syntax* Console::getKey(const string& name) const
{
	if(command == nullptr)
		return nullptr;
	auto res = command->syntax.find(name);
	if(res == command->syntax.end())
		return nullptr;
	return &(res->second);
}


const map<string, Command*>& Console::getCommand() const
{
	return commands;
}



// 输入状态, 当前在输入的部分
enum class State
{
	COMMAND, // 输入命令
	KEY,		 // 输入键
	VALUE		 // 输入值
};


// 高亮信息
struct Highlight
{
	struct Tuple
	{
		Attribute::fore fore;
		// Attribute::back back;
		Attribute::mode mode;
	};

	Tuple command;
	Tuple key;
	Tuple value;
	Tuple string;
	Tuple number;
	Tuple delim;
};


template <typename T>
auto GetMapKeyByValue(const T& map_, const decltype(map_.begin()->second)& value) -> decltype(map_.begin()->first)
{
	auto iter = std::find_if(map_.begin(), map_.end(), [value](const auto& item) {
		return (item.second == value);
	});

	if(iter == map_.end())
	{
		return decltype(map_.begin()->first)();
	}
	return iter->first;
}


void Console::run()
{
	Highlight highlight;
	highlight.command.fore = Attribute::fore::green;
	highlight.command.mode = Attribute::mode::fore_bold;
	highlight.key.fore		 = Attribute::fore::yellow;
	highlight.key.mode		 = Attribute::mode::fore_bold;

	while(true)
	{
		string					buf;
		vector<Syntax*> keys;
		State						state				= State::COMMAND;
		string*					arg					= nullptr;
		size_t					pos					= 0;
		const string*		match				= nullptr;
		bool						inputString = false;

		PrintPrompt();

		while(true)
		{
			char ch = GetChar();


			if(ch == '\r')
			{
				if(state == State::VALUE)
					*arg = buf;
				printf("\n");
				break;
			}


			// 处理特殊字符
			switch(ch)
			{
			case ' ':
				switch(state)
				{
				case State::COMMAND:
					if(command == nullptr)
						continue;
					state = State::KEY;
					buf.clear();
					break;

				case State::VALUE:
					if(inputString)
					{
						buf += ch;
						break;
					}
					*arg	= buf;
					state = State::KEY;
					buf.clear();
					break;

				case State::KEY:
					continue;
				}
				printf(" ");
				continue;

			case ':':
				if(state != State::KEY || key == nullptr)
					continue;
				printf(":");
				arg		= &args[buf];
				state = State::VALUE;
				buf.clear();
				continue;

			case '\b':
				switch(state)
				{
				case State::COMMAND:
					if(buf.empty())
						continue;
					printf("\b \b");
					buf.pop_back();
					break;

				case State::KEY:
					if(buf.empty())
						; // 还原buf
					printf("\b \b");
					buf.pop_back();
					break;
				}
				break;

			case '\t':
				if(match == nullptr)
					continue;
				printf("%s", match->substr(buf.size(), pos).c_str());
				buf += match->substr(buf.size(), pos);
				break;

			default:
				// 输入合法性检查
				switch(state)
				{
				case State::COMMAND:
				case State::KEY:
					if(!isalnum(ch))
						continue;
					break;

				case State::VALUE:
					switch(key->type)
					{
					case Syntax::Type::STRING:
						if(!isprint(ch))
							continue;
						if(ch == '"')
						{
							if(!inputString)
								inputString = true;
							else
								inputString = false;
						}
						break;

					case Syntax::Type::INT:
						if(!isdigit(ch))
							continue;
						break;

					case Syntax::Type::FLOAT:
					case Syntax::Type::DOUBLE:
						if(!isdigit(ch) && ch != '.')
							continue;
						break;
					}
					break;
				}
			}


			if(isprint(ch))
			{
				printf("%c", ch);
				buf += ch;
			}


			// 识别关键字 并 高亮
			switch(state)
			{
			case State::COMMAND:
				command = getCommand(buf);
				if(command != nullptr)
				{
					Attribute::set(highlight.command.fore);
					Attribute::set(highlight.command.mode);
				}
				for(size_t i = 0; i < buf.size(); i++)
					printf("\b \b");
				printf("%s", buf.c_str());
				Attribute::rest();
				break;

			case State::KEY:
				key = getKey(buf);
				if(key != nullptr)
				{
					Attribute::set(highlight.key.fore);
					Attribute::set(highlight.key.mode);
				}
				for(size_t i = 0; i < buf.size(); i++)
					printf("\b \b");
				printf("%s", buf.c_str());
				Attribute::rest();
				break;
			}


			vector<const string*> matchs;
			switch(state)
			{
			case State::COMMAND:
				for(auto& cmd : commands)
					if(buf == cmd.first.substr(0, buf.size()))
						matchs.push_back(&cmd.first);

				if(matchs.size() == 0)
				{
					match = nullptr;
					break;
				}

				match = matchs.back();

				if(matchs.size() > 1)
				{
					matchs.pop_back();
					pos = 0;
					for(auto i = buf.size(); pos; i++)
					{
						for(auto cmd : matchs)
							if(cmd->size() <= i - 1 || (*cmd)[i] != (*match)[i])
							{
								pos = i - buf.size();
								break;
							}
					}
				}
				else
					pos = match->size() - buf.size();
				break;

			case State::KEY:
				break;
			}
			matchs.clear();
		}

		buf.clear();

		try
		{
			assert(command != nullptr);
			command->excute(*this);
		}
		catch(const char* error)
		{
			print::error(error);
		}
		catch(...)
		{
			print::error("发生错误");

			string strCmd = GetMapKeyByValue(commands, command);
			print::info("卸载命令: " + strCmd);
			delCommand(strCmd);
		}
	}
}


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
