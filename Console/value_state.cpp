// Copyright 2020 SMS
// License(Apache-2.0)

#include "value_state.h"
#include <ctype.h>
#include "console_input.h"
#include "end_state.h"
#include "key_state.h"

using std::string;

ValueState::ValueState(const string& s)
{
	str = s;
}

InputState* ValueState::handle(ConsoleInput& c, input_t in)
{
	switch (in)
	{
	case '\n':
	case '\r':
		printf("\n");
		c.values.push_back(str);
		return new EndState();

	case ' ':
	case '\t':
		printf("%c", in);
		c.values.push_back(str);
		return new KeyState();

	case '\b':
		printf("\b \b");
		if(!str.empty())
			str.pop_back();
		else
		{
			auto key = c.keys.back();
			c.keys.pop_back();
			return new KeyState(key);
		}
		return nullptr;
	}

	if(!isprint(in) && in != '_')
		return nullptr;

	printf("%c", in);
	str.push_back(in);

	return nullptr;
}
