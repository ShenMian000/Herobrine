// Copyright 2019 SMS
// License(Apache-2.0)

#include "print.h"
#include "attribute.h"

using std::string;
using std::mutex;


mutex print::mutex;


void print::info(const string& str)
{
	mutex.lock();
	attribute::set(attribute::fore::blue);
	attribute::set(attribute::mode::fore_bold);
	printf("[*] ");
	attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}

void print::good(const string& str)
{
	mutex.lock();
	attribute::set(attribute::fore::green);
	attribute::set(attribute::mode::fore_bold);
	printf("[+] ");
	attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}

void print::error(const string& str)
{
	mutex.lock();
	attribute::set(attribute::fore::red);
	attribute::set(attribute::mode::fore_bold);
	printf("[-] ");
	attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}

void print::warn(const string& str)
{
	mutex.lock();
	attribute::set(attribute::fore::yellow);
	attribute::set(attribute::mode::fore_bold);
	printf("[!] ");
	attribute::rest();
	puts(str.c_str());
	mutex.unlock();
}
