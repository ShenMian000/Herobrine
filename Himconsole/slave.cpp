// Copyright 2019 SMS
// License(Apache-2.0)
// 被控端

#include "slave.h"

using namespace boost;



Slave::Slave(asio::ip::tcp::socket& sock)
		: sock(sock)
{
}


// 发送数据
void Slave::sendAsync(const string& buf)
{
}

// 接收数据
void Slave::recvAsync(string& buf)
{
}


// 获取 IP地址
const std::string& Slave::getIpAddress()
{
	return sock.remote_endpoint().address().to_string();
}


// 更新基本信息
void Slave::update()
{
}

/*
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
	char* pBuf = new char[sizeof(osInfo)+sizeof(userInfo)];

	memset(pBuf, '\0', sizeof(*pBuf));
	memcpy(pBuf, &osInfo, sizeof(osInfo));
	pBuf += sizeof(osInfo);
	memcpy(pBuf, &userInfo, sizeof(userInfo));

	delete[] pBuf;
}
*/
