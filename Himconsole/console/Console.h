// Copyright 2019 SMS
// License(Apache-2.0)
// 命令行

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../include.h"
#include "../print.h"
#include "command.h"
#include "AutoComplete.h"
#include "Highlight.h"



// 输入状态, 当前在输入的部分
enum class State
{
	COMMAND, // 输入命令
	KEY,		 // 输入键
	DELIM,	 // 输入分隔符
	VALUE		 // 输入值
};

class Console
{
public:
	Console();
	virtual ~Console();

	void run();

	const std::string& getStringArg(const std::string& key) const;
	int								 getIntArg(const std::string& key) const;
	long							 getLongArg(const std::string& key) const;
	size_t						 getArgSize() const;

	void		 addCommand(const std::string& name, Command*);
	void		 delCommand(const std::string& name);
	Command* getCommand(const std::string& name) const;

	void setPrompt(const std::string&);

	void setHistorySize(size_t);
	void addHistory(const vector<std::string>&) const;

	const map<std::string, Command*>& getCommand() const;
	const deque<std::string>&					getHistory() const;

private:
	map<std::string, std::string> args; // 参数
	map<std::string, Command*>		commands;
	deque<std::string>						historys;					// 命令历史记录
	size_t												historySize = 30; // 最大命令历史记录数量
	std::string										prompt;						// 命令行提示符
	State													state;
	AutoComplete									autoComplete;
	Highlight											highlight;

	string												buf;


	Command*			pCommand = nullptr;
	const Syntax* pKey		 = nullptr;

	virtual void		PrintPrompt();
	inline int			GetChar(); // 读入一个字符, 不回显
	const Syntax*		getKey(const std::string& name) const;
	bool						isFilled(const Syntax*);
	vector<Syntax*> filled;
};



#endif // CONSOLE_H_
