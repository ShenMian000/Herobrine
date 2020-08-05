// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CONSOLE_INPUT_H_
#define CONSOLE_INPUT_H_

#include <string>
#include <vector>
#include "command_state.h"
#include "key_state.h"
#include "value_state.h"

class ConsoleInput
{
public:
	ConsoleInput();

	void handle(input_t);
	bool isEnded();

	void setState(InputState*);

	// TODO(SMS): ·â×°Êý¾Ý
	std::string              command;
	std::vector<std::string> keys;
	std::vector<std::string> values;
	
private:
	InputState* pState;
};

#endif // CONSOLE_INPUT_H_
