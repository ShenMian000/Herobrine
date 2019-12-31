// Copyright 2019 SMS
// License(Apache-2.0)
// 

#include "command.h"
#include "console.h"
#include "localization.h"



Command::Command(
		const string& desc,
		const string& author,
		Platform      platform,
		License       license)
	: desc(desc),
	  author(author),
	  platform(platform),
	  license(license)
{
}


Command::~Command()
{
}





