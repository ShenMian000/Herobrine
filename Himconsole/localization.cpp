// Copyright 2019 SMS
// License(Apache-2.0)
// ±¾µØ»¯

#include "localization.h"

using std::string;



Localization local;

const string& Localization::operator[](const string& str)
{
	return dir[str];
}


