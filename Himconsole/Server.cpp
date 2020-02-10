// Copyright 2019 SMS
// License(Apache-2.0)
//

#include "Server.h"
#include "Session.h"
#include <boost/bind.hpp>
#include "print.h"

using namespace boost;



Server::Server(ushort port)
		: acceptor(ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
}


// 开始异步通信
void Server::run()
{
	ios.run();



	print::info("开始监听: " + acceptor.local_endpoint().address().to_string() + ":" + to_string(acceptor.local_endpoint().port()));

	Accept();
}


// 新连接建立时回调
void Server::OnAccept(const system::error_code& err, socket_ptr sock)
{
	if(err)
		return;

	print::good("客户端接入: " + sock->remote_endpoint().address().to_string() + ":" + to_string(sock->remote_endpoint().port()));

	// 添加新客户端
	Session session(ios);

	Accept();
}


// 异步监听
void Server::Accept()
{
	socket_ptr sock(new asio::ip::tcp::socket(ios));
	acceptor.async_accept(*sock, boost::bind(&Server::OnAccept, this, asio::placeholders::error, sock));
}
