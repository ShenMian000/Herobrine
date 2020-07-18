// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_COLOR_H_
#define CLEM_COLOR_H_

#include <string>
#include "os.h"

#ifdef OS_WIN
	#include <windows.h>
#endif


class Color
{
public:
	enum class Fore;
	enum class Back;

	Color(Fore, Back, bool = true, bool = false, bool = false);
	Color(Fore, bool = true, bool = false, bool = false);
	Color(Back, bool = true, bool = false, bool = false);

	void print(const std::string&);

	void on();
	void off();

	Fore getFore() const;
	Back getBack() const;

	void setFore(Fore);
	void setBack(Back);

private:
	void Compile();

	Fore fore;
	Back back;
	bool bold;
	bool underline;
	bool reverse;

#ifdef OS_LINUX
	std::string attribute;
#endif

#ifdef OS_WIN
	WORD   attribute;
	WORD   defAttribute;
	HANDLE hStdOut = NULL;
#endif
};

// Ç°¾°É«
enum class Color::Fore
{
#ifdef OS_LINUX
	black	 = 0,
	red		 = 1,
	green	 = 2,
	yellow = 3,
	blue	 = 4,
	purple = 5,
	cyan	 = 6,
	aqua	 = 6,
	white	 = 7,
	none
#endif

#ifdef OS_WIN
			black = 0,
	blue			= 1,
	green			= 2,
	cyan			= 3,
	aqua			= 3,
	red				= 4,
	purple		= 5,
	yellow		= 6,
	white			= 7,
	none
#endif
};

// ±³¾°É«
enum class Color::Back
{
#ifdef OS_LINUX
	black	 = 0,
	red		 = 1,
	green	 = 2,
	yellow = 3,
	blue	 = 4,
	purple = 5,
	cyan	 = 6,
	aqua	 = 6,
	white	 = 7,
	none
#endif

#ifdef OS_WIN
			black = 0,
	blue			= 1,
	green			= 2,
	cyan			= 3,
	aqua			= 3,
	red				= 4,
	purple		= 5,
	yellow		= 6,
	white			= 7,
	none
#endif
};

#endif // CLEM_COLOR_H_
