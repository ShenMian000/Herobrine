// Copyright 2019 SMS
// License(Apache-2.0)

#include "Herobrine.h"
#include <string>

using std::string;
using namespace boost;



Herobrine::Herobrine(boost::asio::io_context& ioc, const std::string& ip, unsigned short port)
		: Session(ioc, ip, port)
{
}


void Herobrine::OnConnect(const boost::system::error_code& error)
{
	if(error)
	{
		// 无法连接到服务器
		Connect();
		return;
	}

	Read();

	Connect();
}


void Herobrine::OnRead(const boost::system::error_code& error, size_t len)
{
	if(error)
		return;

	puts(buffer);

	Read();
}
