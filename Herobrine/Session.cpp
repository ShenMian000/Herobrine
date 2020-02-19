
#include "Session.h"
#include <boost/bind.hpp>

using std::string;
using namespace boost;

Session::Session(boost::asio::io_context& ioc, const std::string& ip, unsigned short port)
		: sock(ioc), endpoint(asio::ip::address::from_string(ip), port)
{
	Connect();
}

Session::~Session()
{
}



void Session::Connect()
{
	sock.async_connect(endpoint, boost::bind(&Session::OnConnect, this, asio::placeholders::error));
}

void Session::Write(const string& buf)
{
	asio::async_write(sock, asio::buffer(buf), boost::bind(&Session::OnWrite, this, asio::placeholders::error));
}

void Session::Read()
{
	memset(buffer, sizeof(buffer), '\0');
	sock.async_read_some(asio::buffer(buffer), boost::bind(&Session::OnRead, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
}


void Session::OnConnect(const boost::system::error_code& error)
{
}

void Session::OnWrite(const boost::system::error_code& error)
{
}

void Session::OnRead(const boost::system::error_code& error, size_t len)
{
}
