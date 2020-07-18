// Copyright 2020 SMS
// License(Apache-2.0)

#include "console.h"
#include <assert.h>
#include <stdexcept>

using namespace std;

void Console::execute(const std::string& cmd)
{
	
}

const string& Console::getStringArg(const string& key)
{
	try
	{
		return args.at(key);
	}
	catch(std::out_of_range)
	{
		// 尝试访问不存在的参数
		assert(false);
	}
}
