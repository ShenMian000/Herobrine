// Copyright 2019 SMS
// License(Apache-2.0)

#ifndef CONSOLE_COMMAND_H_
#define CONSOLE_COMMAND_H_

#include <string>
#include <map>



class Command
{
public:
	enum class Platform;
	struct Syntax;

	Command(
			const std::string& desc,
			const std::string& author,
			Platform					 platform);

	virtual void excute(std::map<std::string, std::string>&) = 0;

	const std::string& getDescription() const;
	const std::string& getAuthor() const;
	Platform					 getPlatform() const;

protected:
	void addSyntax(const std::string&, const Syntax&);

private:
	const std::string							desc;
	const std::string							author;
	const Platform								platform;
	std::map<std::string, Syntax> syntax;
};



enum class Command::Platform
{
	Common,
	Windows,
	Linux
};


struct Command::Syntax
{
	enum class Type
	{
		String,
		Int,
		Float,
		Option
	};

	Syntax(Type type, const std::string desc, bool required)
			: type(type), desc(desc), required(required)
	{
	}

	Type				type;
	std::string desc;
	bool				required;
};



#endif // CONSOLE_COMMAND_H_
