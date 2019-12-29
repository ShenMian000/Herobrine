// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef COMMAND_H_
#define COMMAND_H_

#include "include.h"



// 运行平台
enum class Platform
{
	Common,
	Windows_XP,
	Windows_10,
};

// 开源协议类型
enum class License
{
	Apache_2_0,
	BSD,
	GPL_3_0,
	MPL_2_0,
	LGPL_3_0,
	TIM,
};

struct Argument
{
	Argument()
		: Long(0)
	{
	}

	~Argument()
	{
		String.~String();
	}

	enum class Type
	{
		Int,     // 整型   long
		String,  // 字符串 std::string
	};

	union
	{
		long   Long;
		string String; // TODO(SMS): string能否在正确的时候被析构?
	};
};

class  Console;


class Command
{
	friend class Console;

public:
	Command(
		const string& name,
		const string& desc,
		const string& author,
		Platform      platform = Platform::Common,
		License       license  = License::Apache_2_0
	);
	virtual ~Command();

	const string& getName();
	const string& getDescription();
	const string& getAuthor();
	Platform      getPlatform();
	License       getLicense();

	virtual void excute(Console&) = 0;  // 执行命令

protected:
	string   name;
	string   desc;
	string   author;
	Platform platform;
	License  license;
	map<string, Argument::Type> syntax;
};



#endif // COMMAND_H_
