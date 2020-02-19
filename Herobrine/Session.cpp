
#include "Session.h"
#include <boost/bind.hpp>

using namespace boost;

Session::Session(const std::string& ip, unsigned short port)
		: sock(ios), endpoint(asio::ip::address::from_string(ip), port)
{
}

Session::~Session()
{
}


void Session::run()
{
	Connect();
	ios.run();
}


void Session::Connect()
{
	sock.async_connect(endpoint, boost::bind(&Session::OnConnect, this, asio::placeholders::error));
}

void Session::Send(const std::string& buf)
{
	sock.async_write_some(asio::buffer(buf), boost::bind(&Session::OnSend, this, asio::placeholders::error));
}

void Session::Recv(std::string&)
{
}


void Session::OnConnect(const boost::system::error_code&)
{
}

void Session::OnSend(const boost::system::error_code&, size_t)
{
}
