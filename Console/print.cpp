// Copyright 2020 SMS
// License(Apache-2.0)

#include "print.h"
#include "color.h"

using std::string;
using std::mutex;


mutex Print::mutex;


void Print::info(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::blue);
	Color::set(Color::Mode::fore_bold);
	printf("[*] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}

void Print::good(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::green);
	Color::set(Color::Mode::fore_bold);
	printf("[+] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}

void Print::error(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::red);
	Color::set(Color::Mode::fore_bold);
	printf("[-] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}

void Print::warn(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::yellow);
	Color::set(Color::Mode::fore_bold);
	printf("[!] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}
