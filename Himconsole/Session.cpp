// Copyright 2019 SMS
// License(Apache-2.0)
// 被控端

#include "Session.h"
#include "Server.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using std::string;
using namespace boost;



Session_::Session_(asio::io_service& ios)
		: sock(ios)
{
}


// 发送数据
void Session_::send(const string& buf)
{
	//asio::async_write(sock, asio::buffer(buf),
	//	boost::bind(&Session::OnSend, this, asio::placeholders::error));
}

// 回调: 发送完成后
void Session_::OnSend()
{
}


// 接收数据
void Session_::recv(string& buf)
{
	//asio::async_read(sock, asio::buffer(buf),
	//	boost::bind(&Session::OnRecv, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
}

// 回调: 可以接收时
void Session_::OnRecv()
{
}


// 获取 IP地址
const string& Session_::ipAddress() const
{
	return sock.remote_endpoint().address().to_string();
}

// 获取 端口
ushort Session_::port() const
{
	return sock.remote_endpoint().port();
}


// 更新基本信息
void Session_::update()
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
