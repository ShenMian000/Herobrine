// Copyright 2019 SMS
// License(Apache-2.0)

#include "command.h"

using std::string;



Command::Command(const std::string& desc,
								 const std::string& author,
								 Platform						platform)
		: desc(desc), author(author), platform(platform)
{
}


const std::string& Command::getDescription() const
{
	return desc;
}

const std::string& Command::getAuthor() const
{
	return author;
}

Command::Platform Command::getPlatform() const
{
	return platform;
}


// Ìí¼ÓÓï·¨
void Command::addSyntax(const std::string& name, const Syntax& syntax)
{
	this->syntax.insert({name, syntax});
}


