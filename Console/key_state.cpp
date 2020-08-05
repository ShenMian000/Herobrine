// Copyright 2020 SMS
// License(Apache-2.0)

#include "key_state.h"
#include <ctype.h>
#include "console_input.h"
#include "value_state.h"
#include "command_state.h"

using std::string;

KeyState::KeyState(const string& s)
{
	str = s;
}

InputState* KeyState::handle(ConsoleInput& c, input_t in)
{
	switch(in)
	{
	case ':':
		printf(":");
		c.keys.push_back(str);
		return new ValueState();

	case '\b':
		printf("\b \b");
		if(!str.empty())
			str.pop_back();
		else
		{
			if(c.keys.empty())
				c.setState(new CommandState(c.command));
			else
			{
				c.setState(new KeyState(c.keys.back()));
				c.keys.pop_back();
			}
		}
	}

	if(!isalnum(in) && in != '_')
		return nullptr;

	static Color yellow(Color::Fore::yellow);
	yellow.on();
	printf("%c", in);
	yellow.off();
	str.push_back(in);

	return nullptr;
}
