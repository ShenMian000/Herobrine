// Copyright 2019 SMS
// License(Apache-2.0)

#include "include.h"
#include <boost/asio.hpp>

using namespace boost;



int main()
{
	asio::io_service			ios;
	asio::ip::tcp::socket sock(ios);

	asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"), 25565);
	sock.connect(endpoint);

	puts("连接成功");

	sock.write_some(asio::buffer("Hello, Himconsole!"));

	getchar();
	getchar();

	return 0;
}
