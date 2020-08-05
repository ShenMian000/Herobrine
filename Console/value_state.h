// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef VALUE_STATE_H_
#define VALUE_STATE_H_

#include "input_state.h"

class ValueState : public InputState
{
public:
	ValueState(const std::string& = std::string());
	InputState* handle(ConsoleInput&, input_t);
};

#endif // VALUE_STATE_H_
