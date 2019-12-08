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
typedef struct
{
	os_type type;
} os_info;


// 目标用户基本信息
typedef struct
{
	char* name; // 用户名称
} user_info;


// 模块信息
typedef struct
{
	char*	path;     // 路径
	char* auther;   // 作者
	char* license;  // 许可证
} module_info;


class Slave
{
public:
	Slave();
	~Slave();

	bool Load(const string& mod);   // 装载模块
	bool Unload(const string& mod); // 卸载模块

private:
	os_info   os_info;                 // 系统信息
	user_info user_info;               // 用户信息
	forward_list<module_info*> module; // 已装载的模块

	void OnAccept();
};



#endif // SLAVE_H_
