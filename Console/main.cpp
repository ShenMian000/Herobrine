// Copyright 2020 SMS
// License(Apache-2.0)

#include <stdio.h>
#include "service_locator.h"
#include "print.h"

int main()
{
	ServiceLocator sl;
	
	std::mutex out;
	Print*     print = new Print(out);

	return 0;
}
