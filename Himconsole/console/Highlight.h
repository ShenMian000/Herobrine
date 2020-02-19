// Copyright 2019 SMS
// License(Apache-2.0)
// ∏ﬂ¡¡

#include "../include.h"
#include "../attribute.h"
#include "Command.h"

#ifndef HIGHLIGHT_H_
#define HIGHLIGHT_H_



enum class State;

class Highlight
{
public:
	Highlight();
	explicit Highlight(Console*);

	void run(State, const std::string&, const Command*, const Syntax*);

	void setCommandFore(attribute::fore);
	void setCommandMode(attribute::mode);
	void setKeyFore(attribute::fore);
	void setKeyMode(attribute::mode);
	void setDelimFore(attribute::fore);
	void setDelimMode(attribute::mode);

private:
	struct
	{
		struct
		{
			attribute::fore fore;
			attribute::mode mode;
		} command, key, delim, string, number;
	} color;
	Console* console;
};



#endif // HIGHLIGHT_H_
