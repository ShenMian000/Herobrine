// Copyright 2020 SMS
// License(Apache-2.0)

#include "print.h"
#include "color.h"

using std::string;

Print::Print(std::mutex& m)
		: mutex(m)
{
}

void Print::info(const string& str)
{
	static Color blue(Color::Fore::blue);
	mutex.lock();
	blue.print("[*] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::good(const string& str)
{
	static Color green(Color::Fore::green);
	mutex.lock();
	green.print("[+] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::error(const string& str)
{
	static Color red(Color::Fore::red);
	mutex.lock();
	red.print("[-] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::warn(const string& str)
{
	static Color yellow(Color::Fore::yellow);
	mutex.lock();
	yellow.print("[!] ");
	puts(str.c_str());
	mutex.unlock();
}
