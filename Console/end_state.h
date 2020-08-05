// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef END_STATE_H_
#define END_STATE_H_

#include "input_state.h"
#include <string>

class EndState : public InputState
{
public:
	void        enter(ConsoleInput&);
	InputState* handle(ConsoleInput&, input_t);
};

#endif // END_STATE_H_
