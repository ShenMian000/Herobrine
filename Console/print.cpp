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
	Color(Color::Fore::blue).print("[*] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::good(const string& str)
{
	mutex.lock();
	Color(Color::Fore::green).print("[+] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::error(const string& str)
{
	mutex.lock();
	Color(Color::Fore::red).print("[-] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::warn(const string& str)
{
	mutex.lock();
	Color(Color::Fore::yellow).print("[!] ");
	puts(str.c_str());
	mutex.unlock();
}
