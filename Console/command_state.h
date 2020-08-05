// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef COMMAND_STATE_H_
#define COMMAND_STATE_H_

#include <string>
#include "input_state.h"

class CommandState : public InputState
{
public:
	CommandState(const std::string& = std::string());
	InputState* handle(ConsoleInput&, input_t);
};

#endif // COMMAND_STATE_H_
