// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

// 涵盖一个普通命令行该具备的功能
// Himconsole加入而外的功能, 比如模块API GetSessionInfo...

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "include.h"
#include "command.h"
#include "print.h"



enum class Type
{
	Int,     // 整型
	Short,   // 短整型
	Long,    // 长整型
	String,  // 字符串
};

struct arg
{
	Type  type;
	void* value;
};


class Console
{
public:
	Console();
	virtual ~Console();

	size_t        getArgSize();          // 获取参数数量
	const string& getArg(const string&); // 获取参数

	void setPrompt(const string&);
	void setHistorySize(size_t);

	void addCommand(Command*);
	void delCommand(Command*);

	void console();

private:
	map<string, string>    args;
	vector<Command*>    command;
	deque<string>       history;           // 命令历史记录
	size_t              historySize = 10;  // 最大命令历史记录数量
	string              prompt;            // 命令行提示符

	string ReadLine();
	void   SplitCmdToArg(const string& cmd);
	bool   CheckSyntax();
	inline char  getch(); // 读入单个字符, 不回显
	virtual void PrintPrompt();
};



#endif // CONSOLE_H_
