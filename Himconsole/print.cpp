// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "Print.h"



void Print::info(const string& str)
{
	Attribute::set(Attribute::Fore::blue);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[*] ");
	Attribute::rest();
	puts(str.c_str());
}

void Print::good(const string& str)
{
	Attribute::set(Attribute::Fore::green);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[+] ");
	Attribute::rest();
	puts(str.c_str());
}

void Print::error(const string& str)
{
	Attribute::set(Attribute::Fore::red);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[-] ");
	Attribute::rest();
	puts(str.c_str());
}

void Print::warn(const string& str)
{
	Attribute::set(Attribute::Fore::yellow);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[!] ");
	Attribute::rest();
	puts(str.c_str());
}
