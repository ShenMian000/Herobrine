// Copyright 2019 SMS
// License(Apache-2.0)
//

#include "Server.h"
#include "slave.h"
#include <boost/bind.hpp>
#include "print.h"

using namespace boost;



Server::Server(ushort port)
		: acceptor(ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
}


// 开始
void Server::listen()
{
	Print::info("开始监听: " + acceptor.local_endpoint().address().to_string() + ":" + to_string(acceptor.local_endpoint().port()));

	Listen();
}


// 新连接建立时回调
void Server::OnAccept(const system::error_code& err, socket_ptr sock)
{
	if(err)
		return;

	Print::good("客户端接入: " + sock->remote_endpoint().address().to_string() + ":" + to_string(sock->remote_endpoint().port()));

	// 添加新客户端
	Session slave(*sock);

	Listen();
}


// 异步监听
void Server::Listen()
{
	socket_ptr sock(new asio::ip::tcp::socket(ios));
	acceptor.async_accept(*sock, boost::bind(&Server::OnAccept, this, asio::placeholders::error, sock));
}
