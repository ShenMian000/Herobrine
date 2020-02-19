// Copyright 2019 SMS
// License(Apache-2.0)

#include "Herobrine.h"
#include <boost/asio.hpp>

using namespace boost;



int main()
{
	asio::io_context ioc;

	Herobrine him(ioc, "127.0.0.1", 25565);

	ioc.run();

	return 0;
}
