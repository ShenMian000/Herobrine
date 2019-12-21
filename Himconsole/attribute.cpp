// Copyright 2019 SMS
// License(Apache-2.0)
// 修改控制台字体属性
// 平台: Windows

#include "attribute.h"



HANDLE hStdOut_;  // 标准输出句柄
WORD   defAttr_;  // 默认属性

WORD   attr_;     // 当前控制台字符属性值

// 设置前景属性
void ConsoleOutAttribute(fore attr)
{
	attr_ &= 0xf0;
	attr_ |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut_, attr_);
}

// 设置背景属性
void ConsoleOutAttribute(back attr)
{
	attr_ &= 0x0f;
	attr_ |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut_, attr_);
}

// 设置共同属性
void ConsoleOutAttribute(mode attr)
{
	attr_ |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut_, attr_);
}

// 还原到默认属性
void ConsoleOutAttributeRest()
{
	attr_ = defAttr_;
	SetConsoleTextAttribute(hStdOut_, attr_);
}


// 自动初始化
class WinAttributeInit
{
public:
	WinAttributeInit()
	{
		hStdOut_ = GetStdHandle(STD_OUTPUT_HANDLE);

		// 获取当前缓冲区字符属性
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(hStdOut_, &bufInfo);
		defAttr_ = bufInfo.wAttributes;
		attr_    = defAttr_;
	}

	~WinAttributeInit()
	{
	}
};

WinAttributeInit winAttributeInit;


