// Copyright 2019 SMS
// License(Apache-2.0)

#include "print.h"
#include "Color.h"

using std::string;
using std::mutex;


mutex print::mutex;


void print::info(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::blue);
	Color::set(Color::Mode::fore_bold);
	printf("[*] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}

void print::good(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::green);
	Color::set(Color::Mode::fore_bold);
	printf("[+] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}

void print::error(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::red);
	Color::set(Color::Mode::fore_bold);
	printf("[-] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}

void print::warn(const string& str)
{
	mutex.lock();
	Color::set(Color::Fore::yellow);
	Color::set(Color::Mode::fore_bold);
	printf("[!] ");
	Color::reset();
	puts(str.c_str());
	mutex.unlock();
}
