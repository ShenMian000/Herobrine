// Copyright 2020 SMS
// License(Apache-2.0)

#include "console.h"

int main()
{
	Console console;

	while(true)
	{
		static Color underline(Color::Fore::none, false, true);
		underline.print("him");
		printf("> ");

		console.inputLine();
	}

	return 0;
}
