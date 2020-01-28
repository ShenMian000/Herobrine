// Copyright 2019 SMS
// License(Apache-2.0)
// ±»¿Ø¶Ë

#ifndef SLAVE_H_
#define SLAVE_H_

#include "include.h"
#include "module.h"



struct user_info
{
	string name;
	enum privilege
	{
	};
};

struct os_info
{
};

class Slave
{
public:
	Slave();

private:
	user_info userInfo;
	os_info		osInfo;
	map<const string, Module*> modules;
};



#endif // SLAVE_H_
