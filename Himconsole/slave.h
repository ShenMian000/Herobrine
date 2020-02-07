// Copyright 2019 SMS
// License(Apache-2.0)
// ±»¿Ø¶Ë

#ifndef SLAVE_H_
#define SLAVE_H_

#include "include.h"
#include "module.h"



struct user_info
{
	uint	 uid;
	string name;
	string email;
};


struct system_info
{
	string osName;
	string language;
	string computer;
	enum
	{
		x64,
		x86
	} architecture;
};


class Slave
{
public:

private:
	user_info									 userInfo;
	system_info								 osInfo;
	map<const string, Module*> modules;
};



#endif // SLAVE_H_
