// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef COMMAND_H_
#define COMMAND_H_

#include "../include.h"



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
	BSD_2_Clause,
	BSD_3_Clause,
	GPL_3_0,
	LGPL_3_0,
	MPL_2_0,
	TIM
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
	
	Syntax(Type type, const string& desc, bool required = true, bool show = true, Syntax* base_required = nullptr, Syntax* base_show = nullptr)
			: type(type), desc(desc), required(required), show(show), base_required(base_required), base_show(base_show)
	{
	}

	Syntax()
			: type(Type::OPTION), required(true), show(true), base_required(nullptr), base_show(nullptr)
	{
	}

	Type		type;
	string  desc;
	bool		required;
	bool		show;
	Syntax* base_required;
	Syntax* base_show;
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

	const string&							 getDescription();
	const string&							 getAuthor();
	const map<string, Syntax>& getSyntax();
	Platform									 getPlatform();
	License										 getLicense();

protected:
	map<string, Syntax> syntax;

private:
	const string	 desc;
	const string	 author;
	const Platform platform;
	const License	 license;

	map<const string, const string> str;

	virtual void excute(Console&) = 0;
};



#endif // COMMAND_H_
