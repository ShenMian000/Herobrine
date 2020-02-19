// Copyright 2019 SMS
// License(Apache-2.0)

#ifndef SESSION_H_
#define SESSION_H_



typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

struct system_info
{
	std::string language;
	std::string architecture;
};


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

	char			  buffer[1024];
	socket_ptr  pSock;
	system_info systemInfo;
};



#endif // SESSION_H_
