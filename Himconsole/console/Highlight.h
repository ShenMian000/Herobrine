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

	void setCommandFore(Attribute::Fore);
	void setCommandMode(Attribute::Mode);
	void setKeyFore(Attribute::Fore);
	void setKeyMode(Attribute::Mode);
	void setDelimFore(Attribute::Fore);
	void setDelimMode(Attribute::Mode);

private:
	Console* console;
	struct
	{
		struct
		{
			Attribute::Fore fore;
			Attribute::Mode mode;
		} command, key, delim, string, number;
	} color;
};



#endif // HIGHLIGHT_H_
