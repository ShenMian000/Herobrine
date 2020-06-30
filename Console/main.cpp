// Copyright 2020 SMS
// License(Apache-2.0)

#include <stdio.h>
#include "console.h"

int main()
{
	Console console;

	while(true)
	{
		printf("him> ");
		console.run();
	}

	return 0;
}
