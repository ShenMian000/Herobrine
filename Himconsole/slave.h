// Copyright 2019 SMS
// License(Apache-2.0)
// 被控端

#ifndef SLAVE_H_
#define SLAVE_H_

#include "include.h"
#include "print.h"



enum class os_type
{
	windows_xp,
	windows_10,
	kali,
};
	

// 目标操作系统基本信息
struct os_info
{
	os_type type;
};


// 目标用户基本信息
struct user_info
{
	char* name; // 用户名称
};


// 模块信息
struct module_info
{
	string path;     // 路径
	string auther;   // 作者
	string license;  // 许可证
};

typedef uint module_id_t;


class Slave
{
public:
	Slave();

	bool load(const string& mod);      // 装载模块
	bool unload(const string& mod);    // 卸载模块

private:
	os_info    osInfo;                 // 系统信息
	user_info  userInfo;               // 用户信息
	map<module_id_t, module_info*> module;    // 已装载的模块
};



#endif // SLAVE_H_
