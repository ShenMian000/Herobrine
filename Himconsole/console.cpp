// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

#include "console.h"
#include "localization.h"



Console::Console()
{
}


Console::~Console()
{
}


// 获取参数数量
size_t Console::getArgSize()
{
	return arg.size();
}


// 获取参数
const string& Console::getArg(const string& key)
{
	return arg[key];
}


void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}

void Console::setHistorySize(size_t size)
{
	historySize = size;
}


void Console::addCommand(Command* cmd)
{
	command.push_back(cmd);
}


void Console::console()
{
	string cmd;
	size_t pos;

	while(true)
	{
		PrintPrompt();
		cmd = ReadLine();

		if (cmd.size() == 0)
			continue;

		// 去除多余空格
		while ((pos = cmd.find("  ")) != string::npos)
			cmd.replace(pos, 2, " ");

		// 添加命令历史记录
		if (history.size() == historySize)
			history.pop_back();
		history.push_front(cmd);
		history.begin()->shrink_to_fit();

		// 分隔命令参数
		size_t lastPos;
		lastPos = cmd.find(' ');
		arg["cmd"] = cmd.substr(0, lastPos);
		

		// 退出命令行
		if (arg["cmd"] == "exit")
			return;

		// 查找并执行命令
		for(auto& c : command)
			if(c->getName() == arg["cmd"])
			{
				print::good("");
				c->excute();
				continue;
			}

		print::error(LOC_ERROR_UNKNOWN_COMMAND);
	}
}


string Console::ReadLine()
{
	string cmd;

	size_t pPredict = -1;    // 输入预测指针
	size_t pHistory = -1;    // 命令历史指针

	while (true)
	{
		char buf = _getch();	// TODO(SMS): 存在可移植性问题

		// 边界检查
		if (cmd.size() >= cmd.max_size())
		{
			print::error(LOC_ERROR_COMMAND_TOO_LONG);
			cmd.clear();
			break;
		}

		// 功能键
		if (buf == -32 || buf == 0)
		{
			buf = _getch();	   // 获取功能键ASCII代码 // TODO(SMS): 存在可移植性问题

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
			
			ConsoleOutAttribute(fore::white);
			ConsoleOutAttribute(mode::fore_bold);
			
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
			ConsoleOutAttribute(fore::white);
			ConsoleOutAttribute(mode::fore_bold);

			printf("%c", buf);
			cmd += buf;
		}

	}

	ConsoleOutAttributeRest();
	
	return cmd;
}


// 输出命令行提示符
void Console::PrintPrompt()
{
		printf("\n");
		ConsoleOutAttribute(mode::underline);
		printf(prompt.c_str());
		ConsoleOutAttributeRest();
		printf("> ");
}


void Console::SplitCmdToArg(const string& cmd)
{
}


// 检查是参数是否合法
bool Console::CheckSyntax()
{
	return false;
}


