// Copyright 2020 SMS
// License(Apache-2.0)

#include "end_state.h"
#include "console_input.h"
#include "command_state.h"

void EndState::enter(ConsoleInput& c)
{
}

InputState* EndState::handle(ConsoleInput& c, input_t in)
{
	return nullptr;
}
