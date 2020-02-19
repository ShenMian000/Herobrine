// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "include.h"


class Server
{
public:
	Server(boost::asio::io_context&, ushort port);

	void run();

private:
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

	void Accept();
	void OnAccept(const boost::system::error_code&, socket_ptr);

	boost::asio::io_context&       ioc;
	boost::asio::ip::tcp::acceptor acceptor;
};
