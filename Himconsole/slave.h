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
struct os_info_
{
	os_type type;
};


// 目标用户基本信息
struct user_info_
{
	char* name; // 用户名称
};


// 模块信息
struct module_info
{
	char*	path;     // 路径
	char* auther;   // 作者
	char* license;  // 许可证
};


class Slave
{
public:
	Slave();

	bool Load(const string& mod);      // 装载模块
	bool Unload(const string& mod);    // 卸载模块

private:
	os_info_   osInfo;                 // 系统信息
	user_info_ userInfo;               // 用户信息
	forward_list<module_info*> module; // 已装载的模块

	void OnAccept();
};



#endif // SLAVE_H_
