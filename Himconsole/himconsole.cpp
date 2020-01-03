// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

#include "himconsole.h"

#include "command/ClearCommand.h"
#include "command/HelpCommand.h"
#include "command/HistoryCommand.h"
#include "command/ExecCommand.h"

#include "localization.h"



Himconsole::Himconsole()
{
}

Himconsole::~Himconsole()
{
}



///////////
/**/
int main()
{
	print::warn(local::WARN_DEBUG);
	printf(
			"  __      __    __\n"
			" |  |    |  |  |__|   __________\n"
			" |  |____|  |   __   |  __  __  |\n"
			" |   ____   |  |  |  |  ||  ||  |\n"
			" |  |    |  |  |  |  |  ||  ||  |\n"
			" |__|    |__|  |__|  |__||__||__|\n"
			"\n"
			" [Herobrine (Alpha)             ]\n"
			" [Update Date: %-17.17s]\n"
			" [Update Time: %-17.17s]\n",
			__DATE__, __TIME__);

	Himconsole console;
	console.setPrompt("him");

	console.addCommand("clear",   dynamic_cast<Command*>(new ClearCommand()));
	console.addCommand("exec",    dynamic_cast<Command*>(new ExecCommand()));
	console.addCommand("help",    dynamic_cast<Command*>(new HelpCommand()));
	console.addCommand("history", dynamic_cast<Command*>(new HistoryCommand()));

	console.run();

	return 0;
}
/**/
///////////







/*

inline vector<string> split(string, char);

// 命令行
void Himconsole::Console()
{
	string cmd;

	while (true)
	{
		// 输出命令提示符
		printf("\n");
		Attribute::set(mode::underline);
		printf(prompt.c_str());
		Attribute::setRest();
		printf("> ");

		cmd = ReadLine();

		if (cmd.size() == 0)
			continue;

		// 拆分命令
		arg = split(cmd, ' ');

		// 添加命令历史记录
		while (history_.size() >= historySize)
			history_.pop_back();
		// TODO(SMS): 去除参数间多余的空白字符
		history_.push_front(cmd);
		history_.begin()->shrink_to_fit();

		cmd.clear();

		// 执行内部命令
		if (arg[0] == "clear" || arg[0] == "cls")
			clear();
		else if (arg[0] == "exit" || arg[0] == "quit")
			return;
		else if (arg[0] == "help")
			help();
		else if (arg[0] == "history")
			history();
		else
		{
			// 执行外部命令
			ushort i;
			for (i = 0; i < cmd_.size(); i++)
				if (arg[0] == cmd_[i].name)
				{
					cmd_[i].func(*this);
					break;
				}
			if (i == cmd_.size())
				print::error("未知命令: " + arg[0]);
		}
	}
}


// 读入命令
string Himconsole::ReadLine()
{
		char   buf;
		string cmd;
	
		size_t pPredict = -1;    // 输入预测指针
		size_t pHistory = -1;    // 命令历史指针

		while (true)
		{
			buf = _getch();

			// 边界检查
			if (cmd.size() + 1 > cmd.max_size())
			{
				print::error("命令过长");
				cmd.clear();
				break;
			}

			// 功能键
			if (buf == -32 || buf == 0)
			{
				buf = _getch();	   // 获取功能键ASCII代码

				// 上/下键 切换命令历史记录
				if (buf == 72)  	 // 上键
				{
					if (history_.empty())
						continue;

					if (pHistory == -1)
						pHistory = 0;
					else if (pHistory < history_.size() - 1)
						pHistory++;
					else
						continue;
				}

				if (buf == 80)	   // 下键
				{
					if (history_.empty())
						continue;

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
					cmd = history_[pHistory];
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
				Attribute::set(fore::white);
				Attribute::set(mode::fore_bold);
				printf("%s", &cmd_[pPredict].name[cmd.size()]);
				cmd += &cmd_[pPredict].name[cmd.size()];
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


			// Backspace键 删除上一个字符
			if (buf == '\b')
			{
				if (cmd.size() <= 0)
					continue;
				printf("\b \b");
				cmd.pop_back();
			}
			else
			{
				// 回显输入的字符
				Attribute::set(fore::white);
				Attribute::set(mode::fore_bold);

				printf("%c", buf);

				cmd += buf;
			}

			// 输出预测提示
			for (ushort i = 0; i < cmd_.size(); i++)
			{
				if (cmd_[i].name.compare(0, cmd.size(), cmd) == 0 && !cmd.empty()) // 匹配成功
				{
					// 擦除其他提示
					if (pPredict != i && pPredict != -1)
					{
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf(" ");
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf("\b");
					}

					// 输出提示
					Attribute::set(fore::gray);
					printf("%s", &cmd_[i].name[cmd.size()]);

					// 光标回退
					for (size_t j = 0; j < cmd_[i].name.size() - cmd.size(); j++)
						printf("\b");

					pPredict = i;

					break;
				}

				if (i + 1 == cmd_.size()) // 无匹配
				{
					if (pPredict != -1 && cmd.size() < cmd_[pPredict].name.size())
					{
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf(" ");
						for (size_t j = 0; j < cmd_[pPredict].name.size() - cmd.size(); j++)
							printf("\b");
						pPredict = -1;
					}
				}
			}
		}

		Attribute::setRest();

		return cmd;
}


// 添加命令
void Himconsole::AddCommand(func_t func, string name, string desc, string help)
{
	cmd_.push_back({ func, name, desc, help });
}


// 设置命令行提示符
void Himconsole::SetPrompt(const string& prompt)
{
	this->prompt = prompt;
}


// 清空命令行缓冲区
void Himconsole::clear()
{
#ifdef OS_WIN
	system("cls");
#elif OS_LINUX
	system("clear");
#endif
}


// 显示帮助信息
void Himconsole::help()
{
	if (arg.size() > 2)
	{
		print::error("参数过多");
		return;
	}

	if (arg.size() == 1)   // 枚举全部命令和描述
	{
		Attribute::set(fore::black);
		Attribute::set(back::cyan);
		printf(" %-8s %-20s\n", "命令", "描述");
		Attribute::setRest();

		for (auto& cmd : cmd_)
			printf(" %-8s %-20s\n", cmd.name.c_str(), cmd.desc.c_str());
		return;
	}

	for (auto& cmd : cmd_)   // 输出指定命令的语法
	{
		if (cmd.name == arg[1])
		{
			printf("%s\n%s", cmd.desc.c_str(), cmd.help.c_str());
			return;
		}
	}

	print::error("未知命令: " + arg[1]);
}


// 显示命令历史纪录
void Himconsole::history()
{
	Attribute::set(fore::black);
	Attribute::set(back::cyan);
	printf(" %-4s %-20s\n", "ID", "命令");
	Attribute::setRest();

	for (size_t i = 0; i < history_.size(); i++)
		printf(" %-4zu %-20s\n", i, history_[i].c_str());
}



// 分割字符串
inline vector<string> split(string str, const char pattern)
{
	vector<string>    ret;
	string::size_type pos;

	str += pattern;

	for (size_t i = 0; i < str.size(); i++)
	{
		pos = str.find(pattern, i);
		if (pos < str.size())
		{
			auto sub = str.substr(i, pos - i);
			ret.push_back(sub);
			i = pos;
		}
	}

	return ret;
}

*/
