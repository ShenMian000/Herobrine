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


class Session_
{
	friend class Server;

public:
	Session_(boost::asio::io_service&);

	void write(const std::string&);
	void read(std::string&);

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
