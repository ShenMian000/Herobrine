// Copyright 2019 SMS
// License(Apache-2.0)

/*
 单例模式
 线程不安全
 */

#include "Console.h"
#include <assert.h>

#include <conio.h>

using std::string;

// 输入状态
// 当前正在输入的内容
enum class InputState
{
	Command,
	Key,
	String,
	Integer,
	Floating
};

// 引号使用情况
enum class QuotationMark
{
	None,
	Single,
	Double
};



Console* Console::instance = nullptr;


Console::Console()
{
}


Console& Console::getInstance()
{
	if(instance == nullptr)
		instance = new Console();
	return *instance;
}


// 开启命令行
void Console::run()
{
	while(true)
	{
		InputState		state					= InputState::Command;
		QuotationMark quotationMark = QuotationMark::None;

		printf(prompt.c_str());

		while(true)
		{
			char c = getch();

			switch(state)
			{
			case InputState::Command:
				break;

			case InputState::Key:
				break;

			case InputState::String:
				break;

			case InputState::Integer:
				break;

			case InputState::Floating:
				break;
			}
		}
	}
}


// 添加命令
//   name : 要添加的命令名称
//   cmd  : 要添加的命令的指针
void Console::addCommand(const std::string& name, Command* cmd)
{
	// 不存在名称
	assert(cmd != nullptr);

	commands.insert({name, cmd});
}


// 设置命令提示符
//   prompt : 要设置的命令提示符
void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}
