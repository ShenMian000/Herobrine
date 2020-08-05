
#include "console_input.h"
#include <typeinfo>
#include <assert.h>
#include "command_state.h"
#include "end_state.h"

using std::string;

ConsoleInput::ConsoleInput()
		: pState(new CommandState())
{
}

void ConsoleInput::handle(input_t in)
{
	assert(pState != nullptr);
	auto p = pState->handle(*this, in);

	if(p == nullptr)
		return;

	p->enter(*this);

	setState(p);
}

bool ConsoleInput::isEnded()
{
	return typeid(*pState) == typeid(EndState);
}

void ConsoleInput::setState(InputState* s)
{
	assert(s != nullptr);
	delete pState;
	pState = s;
}
