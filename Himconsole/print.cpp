// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "print.h"



namespace print
{

void info(const string& str)
{
	Attribute::set(Attribute::fore::blue);
	Attribute::set(Attribute::mode::fore_bold);
	printf("[*] ");
	Attribute::rest();
	puts(str.c_str());
}

void good(const string& str)
{
	Attribute::set(Attribute::fore::green);
	Attribute::set(Attribute::mode::fore_bold);
	printf("[+] ");
	Attribute::rest();
	puts(str.c_str());
}

void error(const string& str)
{
	Attribute::set(Attribute::fore::red);
	Attribute::set(Attribute::mode::fore_bold);
	printf("[-] ");
	Attribute::rest();
	puts(str.c_str());
}

void warn(const string& str)
{
	Attribute::set(Attribute::fore::yellow);
	Attribute::set(Attribute::mode::fore_bold);
	printf("[!] ");
	Attribute::rest();
	puts(str.c_str());
}

} // namespace print
