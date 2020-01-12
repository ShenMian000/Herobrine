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
}

/*
void Console::addHistory(const vector<string>& bufs) const
{
	while(historys.size() >= historySize)
		historys.pop_back();
	historys.push_front(bufs);
}
*/

/*
const deque<vector<string>>& Console::getHistory() const
{
	return historys;
}
*/

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
		Attribute::mode mode;
	};

	Tuple command;
	Tuple key;
	Tuple string;
	Tuple number;
	Tuple delim;
};


// TODO(SMS):
//   语法分析, 而不是直接用command->syntax整个容器中的内容
//   命令历史


void Console::run()
{
	Highlight highlight;
	highlight.command.fore = Attribute::fore::green;
	highlight.command.mode = Attribute::mode::fore_bold;
	highlight.key.fore		 = Attribute::fore::yellow;
	highlight.key.mode		 = Attribute::mode::fore_bold;
	highlight.delim.fore	 = Attribute::fore::white;
	highlight.delim.mode	 = Attribute::mode::fore_bold;

	while(true)
	{
		string				 buf;
		vector<string> buffers;
		State					 state			 = State::COMMAND;
		string*				 arg				 = nullptr;
		size_t				 pos				 = 0;
		const string*	 match			 = nullptr;
		bool					 inputString = false;

		PrintPrompt();

		while(true)
		{
			char ch = GetChar();

			// 清除补全提示
			for(size_t i = 0; i <= pos; i++)
				printf(" ");
			for(size_t i = 0; i <= pos; i++)
				printf("\b \b");


			if(inputString && isprint(ch))
			{
				if(ch == '"')
					inputString = false;
				printf("%c", ch);
				buf += ch;
				continue;
			}


			if(ch == '\r')
			{
				buffers.push_back(buf);
				if(state == State::VALUE)
				{
					if(buf.front() == '"')
						*arg = buf.substr(1, buf.size() - 2);
					else
						*arg = buf;
				}
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
					buffers.push_back(buf);
					state = State::KEY;
					buf.clear();
					break;

				case State::VALUE:
					buffers.push_back(buf);
					if(buf.front() == '"')
						*arg = buf.substr(1, buf.size() - 2);
					else
						*arg = buf;
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

				Attribute::set(highlight.delim.fore);
				Attribute::set(highlight.delim.mode);
				printf(":");
				Attribute::rest();

				buffers.push_back(buf);
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
					buf.pop_back();
					break;

				case State::KEY:
					if(buf.empty())
					{
						buf = buffers.back();
						buffers.pop_back();
						if(buffers.size() == 0)
							state = State::COMMAND;
						else
							state = State::VALUE;
					}
					else
						buf.pop_back();
					break;

				case State::VALUE:
					if(buf.empty())
					{
						buf = buffers.back();
						buffers.pop_back();
						state = State::KEY;
					}
					else
						buf.pop_back();
					break;
				}
				printf("\b \b");
				break;

			case '\t':
				if(match == nullptr)
					continue;
				printf("%s", match->substr(buf.size(), pos).c_str());
				buf += match->substr(buf.size(), pos);
				break;

			default:
				// 输入合法性检查
				if(ch < -1 || ch > 255)
					continue;
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
						if(ch == '"' && buf.size() == 0)
							inputString = true;
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


			// TODO(SMS): 存在大量冗余代码, 可以消除
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
					pos				= 0;
					bool flag = false;
					for(auto i = buf.size();; i++)
					{
						for(auto cmd : matchs)
							if(cmd->size() <= i - 1 || (*cmd)[i] != (*match)[i])
							{
								pos	 = i - buf.size();
								flag = true;
								break;
							}
						if(flag)
							break;
					}
				}
				else
					pos = match->size() - buf.size();

				Attribute::set(Attribute::fore::gray);
				printf("%s", match->substr(buf.size(), pos).c_str());
				for(size_t i = 0; i < pos; i++)
					printf("\b");
				Attribute::rest();
				break;

			case State::KEY:
				for(auto& cmd : command->syntax)
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
					pos				= 0;
					bool flag = false;
					for(auto i = buf.size();; i++)
					{
						for(auto cmd : matchs)
							if(cmd->size() <= i - 1 || (*cmd)[i] != (*match)[i])
							{
								pos	 = i - buf.size();
								flag = true;
								break;
							}
						if(flag)
							break;
					}
				}
				else
					pos = match->size() - buf.size();

				Attribute::set(Attribute::fore::gray);
				printf("%s", match->substr(buf.size(), pos).c_str());
				for(size_t i = 0; i < pos; i++)
					printf("\b");
				Attribute::rest();
				break;
			}
			matchs.clear();
		}

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
			print::error("捕获异常");
			print::info("卸载命令: " + buffers.front());
			delCommand(buffers.front());
		}

		buf.clear();
		buffers.clear();
		args.clear();
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
