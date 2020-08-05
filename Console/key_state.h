// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef KEY_STATE_H_
#define KEY_STATE_H_

#include <string>
#include "input_state.h"

class KeyState : public InputState
{
public:
	KeyState(const std::string& = std::string());
	InputState* handle(ConsoleInput&, input_t);
};

#endif // KEY_STATE_H_
