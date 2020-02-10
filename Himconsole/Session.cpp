// Copyright 2019 SMS
// License(Apache-2.0)
// 被控端

#include "Session.h"

using namespace boost;



Session::Session(asio::ip::tcp::socket& sock)
		: sock(sock)
{
}


// 发送数据
void Session::send(const string& buf)
{
}

// 接收数据
void Session::recv(string& buf)
{
}


// 获取 IP地址
const std::string& Session::getIpAddress()
{
	return sock.remote_endpoint().address().to_string();
}


// 更新基本信息
void Session::update()
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
