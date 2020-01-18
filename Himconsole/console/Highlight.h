// Copyright 2019 SMS
// License(Apache-2.0)
// ∏ﬂ¡¡

#include "../include.h"
#include "../attribute.h"
#include "Command.h"

#ifndef HIGHLIGHT_H_
#define HIGHLIGHT_H_



class Highlight
{
public:
	Highlight();
	explicit Highlight(Console*);

	void run();

	void setCommandFore(Attribute::fore);
	void setCommandMode(Attribute::mode);
	void setKeyFore(Attribute::fore);
	void setKeyMode(Attribute::mode);
	void setDelimFore(Attribute::fore);
	void setDelimMode(Attribute::mode);

private:
	Console* console;
	struct
	{
		struct
		{
			Attribute::fore fore;
			Attribute::mode mode;
		} command, key, delim, string, number;
	} color;
};



#endif // HIGHLIGHT_H_
