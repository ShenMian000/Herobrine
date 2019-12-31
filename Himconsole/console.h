// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "include.h"
#include "command.h"
#include "print.h"



class Console
{
public:
	Console();
	virtual ~Console();

	const string& getStringArg(const string& key);
	int           getIntArg(const string& key);
	long          getLongArg(const string& key);
	size_t        getArgSize();

	void          setHistorySize(size_t);
	const string& getHistory(size_t);
	size_t        getHistorySize();

	void          addCommand(Command*);
	void          delCommand(Command*);
	Command*      getCommand(const string& name);
	Command*      getCommand(size_t);
	size_t        getCommandSize();

	void          setPrompt(const string&);

	void console();

private:
	map<string, string>   args;             // 参数
	map<string, Command*> commands;
	deque<string>				  history;					// 命令历史记录
	size_t							  historySize = 30; // 最大命令历史记录数量
	string							  prompt;						// 命令行提示符

	string       ReadLine();
	void         SplitCmdToArg(const string& cmd);
	bool         CheckSyntax(Command*);
	virtual void PrintPrompt();
	inline  int  Input();                  // 读入一个字符, 不回显
};



#endif // CONSOLE_H_
