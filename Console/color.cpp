// Copyright 2020 SMS
// License(Apache-2.0)

#include "color.h"
#include <stdio.h>
#include <assert.h>

Color::Color(Fore f, Back b, bool bold, bool underline, bool reverse)
	: fore(f), back(b), bold(bold), underline(underline), reverse(reverse)
{
	Compile();
}

Color::Color(Fore f, bool bold, bool underline, bool reverse)
	: fore(f), back(Back::none), bold(bold), underline(underline), reverse(reverse)
{
	Compile();
}

Color::Color(Back b, bool bold, bool underline, bool reverse)
	: fore(Fore::none), back(b), bold(bold), underline(underline), reverse(reverse)
{
	Compile();
}

void Color::print(const std::string& str)
{
	on();
	printf("%s", str.c_str());
	off();
}

void Color::on()
{
#ifdef OS_LINUX
	printf("%s", attribute.c_str());
#endif

#ifdef OS_WIN
	SetConsoleTextAttribute(hStdOut, attribute);
#endif
}

void Color::off()
{
#ifdef OS_LINUX
	printf("\e[0m");
#endif

#ifdef OS_WIN
	SetConsoleTextAttribute(hStdOut, defAttribute);
#endif
}

Color::Fore Color::getFore() const
{
	return fore;
}

Color::Back Color::getBack() const
{
	return back;
}

void Color::setFore(Fore f)
{
	fore = f;
	Compile();
}

void Color::setBack(Back b)
{
	back = b;
	Compile();
}

void Color::Compile()
{
#ifdef OS_LINUX
	attribute = "\e[";

	if(fore != Fore::none)
		attribute += ';' + std::to_string((int)fore + 30);

	if(back != Back::none)
		attribute += ';' + std::to_string((int)back + 40);

	if(bold)
		attribute += ";1";

	if(underline)
		attribute += ";4";

	if(reverse)
		attribute += ";7";

	attribute += 'm';
#endif

#ifdef OS_WIN
	if(hStdOut == NULL)
	{
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// 获取当前缓冲区字符属性
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(hStdOut, &bufInfo);
		defAttribute = bufInfo.wAttributes;
	}

	attribute = defAttribute;
	
	if(fore != Fore::none)
	{
		attribute &= 0xf0;
		attribute |= (int)fore;
	}

	if(back != Back::none)
	{
		attribute &= 0x0f;
		attribute |= (int)back * 0x10;
	}

	if(bold)
		attribute |= FOREGROUND_INTENSITY; // 前景色加强

	if(underline)
		attribute |= COMMON_LVB_UNDERSCORE;

	if(reverse)
		attribute |= COMMON_LVB_REVERSE_VIDEO;
#endif
}
