// Copyright 2019 SMS
// License(Apache-2.0)
// ±»¿Ø¶Ë

#include "include.h"
#include <boost/asio.hpp>



class Client
{
public:
	Client(std::string ip, ushort port);

private:
	boost::asio::io_service			 ios;
	boost::asio::ip::tcp::socket sock;
};
