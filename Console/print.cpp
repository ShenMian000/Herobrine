// Copyright 2020 SMS
// License(Apache-2.0)

#include "Print_service.h"
#include "color.h"

using std::string;

void Print::info(const string& str)
{
	static Color blue(Color::Fore::blue);
	mutex.lock();
	blue.Print("[*] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::good(const string& str)
{
	static Color green(Color::Fore::green);
	mutex.lock();
	green.Print("[+] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::error(const string& str)
{
	static Color red(Color::Fore::red);
	mutex.lock();
	red.Print("[-] ");
	puts(str.c_str());
	mutex.unlock();
}

void Print::warn(const string& str)
{
	static Color yellow(Color::Fore::yellow);
	mutex.lock();
	yellow.Print("[!] ");
	puts(str.c_str());
	mutex.unlock();
}
