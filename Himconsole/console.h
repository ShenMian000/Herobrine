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

	void run();

	const string& getStringArg(const string& key) const;
	int						getIntArg(const string& key) const;
	long					getLongArg(const string& key) const;
	size_t				getArgSize() const;

	void setHistorySize(size_t);
	void addHistory(const vector<string>&) const;

	void		 addCommand(const string& name, Command*);
	void		 delCommand(const string& name);
	Command* getCommand(const string& name) const;

	void setPrompt(const string&);

	const map<string, Command*>& getCommand() const;
	const deque<vector<string>>& getHistory() const;

private:
	map<string, string>   args;             // 参数
	map<string, Command*> commands;
	// deque<vector<string>> historys;					// 命令历史记录
	size_t								historySize = 30; // 最大命令历史记录数量
	string							  prompt;						// 命令行提示符

	virtual void PrintPrompt();
	inline  int  GetChar();                   // 读入一个字符, 不回显

	
	Command* command = nullptr;
	Syntax*	 key		 = nullptr;

	Syntax* getKey(const string& name) const;
};



#endif // CONSOLE_H_
