// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

#include "console.h"
#include "localization.h"




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
	return args.at(key).value;
}

int Console::getIntArg(const string& key)
{
	return stoi(args.at(key).value);
}

long Console::getLongArg(const string& key)
{
	return stol(args.at(key).value);
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


void Console::addCommand(Command* cmd)
{
	command.push_back(cmd);
	command.shrink_to_fit();
}


Command* Console::getCommand(const string& name)
{
	for(size_t i = 0; i < command.size(); i++)
		if(command[i]->getName() == name)
			return command[i];
	return nullptr;
}

Command* Console::getCommand(size_t id)
{
	return command.at(id);
}


size_t Console::getCommandSize()
{
	return command.size();
}



void Console::console()
{
	while(true)
	{
		PrintPrompt();
		string buf = ReadLine();

		if (buf.size() == 0)
			continue;

		// 去除多余空格
		size_t pos;
		while ((pos = buf.find("  ")) != string::npos)
			buf.replace(pos, 2, " ");

		// 添加命令历史记录
		if (history.size() == historySize)
			history.pop_back();
		history.push_front(buf);
		history.begin()->shrink_to_fit();

		// 分隔命令参数
		size_t lastPos;
		lastPos = buf.find(' ');
		string commandName = buf.substr(0, lastPos);
		

		// 退出命令行
		if (commandName == "exit")
			return;

		// 执行命令
		auto cmd = commands[commandName];
		try
		{
			cmd->excute(*this);
		}
		catch(char* error)
		{
			print::error(error);
		}

			CheckSyntax(cmd);

		// print::error(local::ERROR_UNKNOWN_COMMAND);
	}
}


string Console::ReadLine()
{
	string cmd;

	size_t pPredict = -1;    // 输入预测指针
	size_t pHistory = -1;    // 命令历史指针

	while (true)
	{
		char buf = Input();

		// 边界检查
		if (cmd.size() >= cmd.max_size())
		{
			print::error(local::ERROR_COMMAND_TOO_LONG);
			cmd.clear();
			break;
		}

		// 功能键
		if (buf == -32 || buf == 0)
		{
			buf = Input();

			if (history.empty())
				continue;

			// 上/下键 切换命令历史记录
			if (buf == 72)  	 // 上键
			{
				if (pHistory == -1)
					pHistory = 0;
				else if (pHistory < history.size() - 1)
					pHistory++;
				else
					continue;
			}

			if (buf == 80)	   // 下键
			{
				if (pHistory == -1)
					pHistory = 0;
				else if (pHistory > 0)
					pHistory--;
				else
					continue;
			}

			// 切换到指定的命令历史记录
			if (buf == 72 || buf == 80)
			{
				for (size_t i = 0; i < cmd.size(); i++)
					printf("\b \b");
				cmd = history[pHistory];
				printf(cmd.c_str());
			}

			continue;
		}

		// Enter键 结束输入
		if (buf == '\r')
		{
			printf("\n");
			break;
		}

		// Tab键 补全命令
		if (buf == '\t')
		{
			if (pPredict == -1)	// 没有匹配项
				continue;
			
			Attribute::set(Attribute::fore::white);
			Attribute::set(Attribute::mode::fore_bold);
			
			printf("%s", &(command[pPredict]->getName()[cmd.size()]));
			cmd += &(command[pPredict]->getName()[cmd.size()]);

			continue;
		}
		
		// ESC键 清空输入
		if (buf == 27)
		{
			for (size_t i = 0; i < cmd.size(); i++)
				printf("\b \b");

			pPredict = -1;
			pHistory = -1;
			cmd.clear();

			continue;
		}

		// 过滤非法字符
		if (false)
			; // TODO(SMS): 有待完善, 注意代码可读性

		if (buf == '\b')
		{
			// Backspace键 删除上一个字符
			if (cmd.size() <= 0)
				continue;
			printf("\b \b");
			cmd.pop_back();
		}
		else
		{
			// 回显输入的字符
			Attribute::set(Attribute::fore::white);
			Attribute::set(Attribute::mode::fore_bold);

			printf("%c", buf);
			cmd += buf;
		}
	}

	Attribute::rest();
	
	return cmd;
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


void Console::SplitCmdToArg(const string& cmd)
{
}


// 检查是参数是否合法
bool Console::CheckSyntax(Command* cmd)
{
	// TODO: 不需要检测参数是否合法, 只需要在ReadLine里让用户无法输入错误的参数即可

	return false;
}


// 读入一个字符, 不回显
inline int Console::Input() {
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


