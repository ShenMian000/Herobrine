// Copyright 2019 SMS
// License(Apache-2.0)
//

#ifndef PRINT_H_
#define PRINT_H_

#include "attribute.h"



class Print
{
public:
	static void info(const string&);
	static void good(const string&);
	static void error(const string&);
	static void warn(const string&);
};



#endif // PRINT_H_
