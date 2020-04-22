// Copyright 2019 SMS
// License(Apache-2.0)
// 修改控制台字体属性

#ifndef CONSOLE_COLOR_H_
#define CONSOLE_COLOR_H_

#include "os.h"

#ifdef OS_WIN
	#include <windows.h>
#endif

#ifdef OS_LINUX
	#include <stdio.h>
#endif

#include <map>



class Color
{
public:
	enum class Fore
	{
		black	 = 0x00,
		blue	 = 0x01,
		green	 = 0x02,
		cyan	 = 0x03,
		red		 = 0x04,
		purple = 0x05,
		yellow = 0x06,
		white	 = 0x07,
		gray	 = 0x08
	};

	enum class Back
	{
		black	 = 0x00,
		blue	 = 0x10,
		green	 = 0x20,
		cyan	 = 0x30,
		red		 = 0x40,
		purple = 0x50,
		yellow = 0x60,
		white	 = 0x70,
		gray	 = 0x80
	};

	enum class Mode
	{
		underline = 0x8000,
		fore_bold = 0x0008,
		back_bold = 0x0080
	};
	
	struct pair
	{
		Fore fore;
		Back back;
		Mode mode;
	};

	//static void add(unsigned int, Fore, Back, Mode);
	//static void set(unsigned int);

	static void set(Fore);
	static void set(Back);
	static void set(Mode);

	static void reset();

private:
	//static std::map<unsigned int, pair> pairs;

#ifdef OS_WIN

	static HANDLE hStdOut;
	static WORD		attr;    // 当前控制台字符属性值
	static WORD		defAttr; // 默认控制台字符属性值

	friend class WinColorInit;

#endif // OS_WIN
};

#endif // CONSOLE_COLOR_H_
