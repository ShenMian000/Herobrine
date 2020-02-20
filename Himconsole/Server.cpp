// Copyright 2019 SMS
// License(Apache-2.0)
//

#include "Server.h"
#include "Session.h"
#include "print.h"
#include <thread>
#include <boost/bind.hpp>

using std::thread;
using namespace boost;



Server::Server(asio::io_context& ioc, ushort port)
		: ioc(ioc), acceptor(ioc, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
}


// 开始异步通信
void Server::run()
{
	Accept();
}


// 新连接建立时回调
void Server::OnAccept(const system::error_code& err, socket_ptr sock)
{
	if(err)
		return;

	print::good("客户端接入: " + sock->remote_endpoint().address().to_string() + ":" + to_string(sock->remote_endpoint().port()));

	sessions.push_back(new Session(sock));

	Accept();
}


// 异步监听
void Server::Accept()
{
	socket_ptr sock(new asio::ip::tcp::socket(ioc));
	acceptor.async_accept(*sock, boost::bind(&Server::OnAccept, this, asio::placeholders::error, sock));
}
