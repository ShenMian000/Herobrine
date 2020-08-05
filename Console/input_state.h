// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef INPUT_STATE_H_
#define INPUT_STATE_H_

///
#include "color.h"
///

typedef char input_t;
class ConsoleInput;

#include <string>

class InputState
{
public:
	virtual void        enter(ConsoleInput&);               // 切换到当前状态时执行
	virtual InputState* handle(ConsoleInput&, input_t) = 0; // 处理与当前状态有关的事务

	std::string toString() const;

protected:
	std::string str;
};

#endif // INPUT_STATE_H_
