// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "command.h"
#include "console.h"
#include "localization.h"



Command::Command(
		const string& name,
		const string& desc,
		const string& author,
		Platform      platform,
		License       license
	)
	: name(name),
	  desc(desc),
	  author(author),
	  platform(platform),
	  license(license)
{
}


Command::~Command()
{
}


const string& Command::getName()
{
	return name;
}


const string& Command::getDescription()
{
	return desc;
}


const string& Command::getAuthor()
{
	return author;
}


bool Command::checkSyntax(Console& c)
{
	if(c.getArgSize()-1 > syntax.size())
		return false;

	

	return true;
}


