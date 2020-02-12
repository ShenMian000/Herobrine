// Copyright 2019 SMS
// License(Apache-2.0)
//

#include "Print.h"



std::mutex print::mutex;

void print::info(const string& str)
{
	mutex.lock();
	Attribute::set(Attribute::Fore::blue);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[*] ");
	Attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}

void print::good(const string& str)
{
	mutex.lock();
	Attribute::set(Attribute::Fore::green);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[+] ");
	Attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}

void print::error(const string& str)
{
	mutex.lock();
	Attribute::set(Attribute::Fore::red);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[-] ");
	Attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}

void print::warn(const string& str)
{
	mutex.lock();
	Attribute::set(Attribute::Fore::yellow);
	Attribute::set(Attribute::Mode::fore_bold);
	printf("[!] ");
	Attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}
