// Copyright 2019 SMS
// License(Apache-2.0)

#include "Herobrine.h"
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using namespace boost;



int main()
{
	asio::io_context   ioc;
	asio::ssl::context ssl(asio::ssl::context::sslv23);

	Herobrine him(ioc, ssl, "127.0.0.1", 25565);

	ioc.run();

	return 0;
}
