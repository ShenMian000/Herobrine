// Copyright 2020 SMS
// License(Apache-2.0)

#include "command_state.h"
#include <ctype.h>
#include "console_input.h"
#include "key_state.h"

using std::string;

CommandState::CommandState(const string& s)
{
	str = s;
}

InputState* CommandState::handle(ConsoleInput& c, input_t in)
{
	switch(in)
	{
	case ' ':
	case '\t':
		printf("%c", in);
		c.command = str;
		return new KeyState();

	case '\b':
		if(!str.empty())
		{
			printf("\b \b");
			str.pop_back();
		}
		return nullptr;
	}

	if(!isalnum(in) && in != '_')
		return nullptr;

	static Color green(Color::Fore::green);
	green.on();
	printf("%c", in);
	green.off();
	str.push_back(in);

	return nullptr;
}
