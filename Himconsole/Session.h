// Copyright 2019 SMS
// License(Apache-2.0)
// ±»¿Ø¶Ë

#ifndef SLAVE_H_
#define SLAVE_H_

#include "include.h"
#include "module.h"



struct user_info
{
	uint				uid;
	std::string name;
	std::string email;
};


struct system_info
{
	std::string osName;
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
public:
	Session(boost::asio::ip::tcp::socket&);

	void send(const std::string&);
	void recv(std::string&);

	const std::string& getIpAddress();

	void update();

private:
	boost::asio::ip::tcp::socket&		sock;
	user_info												userInfo;
	system_info											osInfo;
	map<const std::string, Module*> modules;
};



#endif // SLAVE_H_
