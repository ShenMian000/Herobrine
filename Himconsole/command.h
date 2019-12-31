// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef COMMAND_H_
#define COMMAND_H_

#include "include.h"



class  Console;

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

// 语法
struct Syntax
{
	enum class Type
	{
		INT,	  // 整型 int
		LONG,   // 长整型 long
		FLOAT,  // 单精度浮点数 float
		DOUBLE, // 双精度浮点数 double
		BOOL,   // 布尔值 bool
		STRING, // 字符串 std::string
		OPTION  // 选项
	};
	
	Syntax(Type type, bool required, const string& desc, Syntax* compliance = nullptr)
			: type(type), required(required), desc(desc), compliance(compliance)
	{
	}

	Type		type;
	bool		required;
	string  desc;
	Syntax* compliance;
};


class Command
{
	friend class Console;

public:
	Command(
		const string& desc,
		const string& author,
		Platform      platform = Platform::Common,
		License       license  = License::Apache_2_0);
	virtual ~Command();

	const string& getDescription();
	const string& getAuthor();

protected:
	map<string, Syntax> syntax;

private:
	string	 desc;
	string	 author;
	Platform platform;
	License	 license;

	virtual void excute(Console&) = 0;
};



#endif // COMMAND_H_
