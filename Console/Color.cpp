// Copyright 2019 SMS
// License(Apache-2.0)
// 修改控制台字体属性

#include "Color.h"

typedef unsigned int uint;

std::map<unsigned int, Color::pair> Color::pairs;



// 添加配色方案
void Color::add(uint id, Fore fore, Back back, Mode mode)
{
	pairs.insert(std::pair<uint, pair>(id, {fore, back, mode}));
}

// 使用配色方案
void Color::set(uint id)
{
	set(pairs[id].fore);
	set(pairs[id].back);
	set(pairs[id].mode);
}


#ifdef OS_WIN

HANDLE Color::hStdOut;
WORD	 Color::attr;
WORD	 Color::defAttr;


// 设置前景色
void Color::set(Fore attr)
{
	Color::attr &= 0xf0;
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}

// 设置背景色
void Color::set(Back attr)
{
	Color::attr &= 0x0f;
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}

// 设置其他属性
void Color::set(Mode attr)
{
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}


// 还原默认属性
void Color::reset()
{
	attr = defAttr;
	SetConsoleTextAttribute(hStdOut, attr);
}


class WinColorInit
{
public:
	WinColorInit()
	{
		Color::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// 获取当前缓冲区字符属性
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(Color::hStdOut, &bufInfo);
		Color::defAttr = bufInfo.wAttributes;
		Color::attr		 = bufInfo.wAttributes;
	}
};

WinColorInit winColorInit;

#endif // OS_WIN
