// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "include.h"
#include <boost/enable_shared_from_this.hpp>


class Server
{
public:
	Server(ushort port);

	void run();

	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
	void OnAccept(const boost::system::error_code&, socket_ptr);

private:
	void Listen();

	boost::asio::io_service				 ios;
	boost::asio::ip::tcp::acceptor acceptor;
};
