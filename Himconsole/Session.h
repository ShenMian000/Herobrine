// Copyright 2019 SMS
// License(Apache-2.0)

#ifndef SESSION_H_
#define SESSION_H_

#include <string>
#include <memory>
#include <boost/asio.hpp>



typedef std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;


class Session
{
public:
	Session(socket_ptr);

	void write(const std::string&);
	void read();

	const std::string& getIp() const;
	unsigned short     getPort() const;

private:
	void OnWrite();
	void OnRead();

	char			 buffer[1024];
	socket_ptr pSock;
};



#endif // SESSION_H_
