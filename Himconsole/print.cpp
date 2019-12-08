// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "print.h"



namespace print
{

void info(const string& str)
{
	ConsoleOutAttribute(fore::blue);
	ConsoleOutAttribute(mode::fore_bold);
	printf("[*] ");
	ConsoleOutAttributeRest();
	puts(str.c_str());
}

void good(const string& str)
{
	ConsoleOutAttribute(fore::green);
	ConsoleOutAttribute(mode::fore_bold);
	printf("[+] ");
	ConsoleOutAttributeRest();
	puts(str.c_str());
}

void error(const string& str)
{
	ConsoleOutAttribute(fore::red);
	ConsoleOutAttribute(mode::fore_bold);
	printf("[-] ");
	ConsoleOutAttributeRest();
	puts(str.c_str());
}

void warn(const string& str)
{
	ConsoleOutAttribute(fore::yellow);
	ConsoleOutAttribute(mode::fore_bold);
	printf("[!] ");
	ConsoleOutAttributeRest();
	puts(str.c_str());
}

} // namespace print
