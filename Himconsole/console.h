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

	void setHistorySize(size_t);
	void addHistory();

	void		 addCommand(const string& name, Command*);
	void		 delCommand(const string& name);
	Command* getCommand(const string& name);

	const map<string, Command*>& getCommand();
	const deque<string>&				 getHistory();

	void          setPrompt(const string&);

	void run();

private:
	map<string, string>   args;             // 参数
	map<string, Command*> commands;
	deque<string>				  historys;					// 命令历史记录
	size_t							  historySize = 30; // 最大命令历史记录数量
	string							  prompt;						// 命令行提示符

	virtual void PrintPrompt();
	inline  int  GetChar();                   // 读入一个字符, 不回显
};



#endif // CONSOLE_H_
