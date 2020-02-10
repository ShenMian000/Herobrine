// Copyright 2019 SMS
// License(Apache-2.0)
// ±»¿Ø¶Ë

#ifndef SLAVE_H_
#define SLAVE_H_

#include "include.h"



class Server;
class Module;

struct user_info
{
	uint				uid;
	std::string name;
	std::string email;
};

struct system_info
{
	std::string os;
	std::string language;
	std::string computer;
	enum
	{
		x64,
		x86
	} architecture;
};


class Session
{
	friend class Server;

public:
	Session(boost::asio::io_service&);

	void send(const std::string&);
	void recv(std::string&);

	void update();

	const std::string& ipAddress() const;
	ushort						 port() const;

private:
	void OnSend();
	void OnRecv();

	boost::asio::ip::tcp::socket sock;
	user_info										 userInfo;
	system_info									 osInfo;
	map<std::string, Module*>		 modules;
};



#endif // SLAVE_H_
