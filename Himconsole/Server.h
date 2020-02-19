// Copyright 2019 SMS
// License(Apache-2.0)

#include <boost/asio.hpp>
#include "Session.h"



class Server
{
public:
	Server(boost::asio::io_context&, ushort port);

	void run();

private:
	void Accept();
	void OnAccept(const boost::system::error_code&, socket_ptr);

	boost::asio::io_context&       ioc;
	boost::asio::ip::tcp::acceptor acceptor;
	std::vector<Session>           sessions;
};
