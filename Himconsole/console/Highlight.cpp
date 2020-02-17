// Copyright 2019 SMS
// License(Apache-2.0)
// ¸ßÁÁ

#include "Highlight.h"
#include "Console.h"



Highlight::Highlight()
		: console(nullptr)
{
	color.command.fore = attribute::fore::green;
	color.command.mode = attribute::mode::fore_bold;
	color.key.fore		 = attribute::fore::yellow;
	color.key.mode		 = attribute::mode::fore_bold;
	color.delim.fore	 = attribute::fore::white;
	color.delim.mode	 = attribute::mode::fore_bold;
}

Highlight::Highlight(Console* console)
		: console(console)
{
	color.command.fore = attribute::fore::green;
	color.command.mode = attribute::mode::fore_bold;
	color.key.fore		 = attribute::fore::yellow;
	color.key.mode		 = attribute::mode::fore_bold;
	color.delim.fore	 = attribute::fore::white;
	color.delim.mode	 = attribute::mode::fore_bold;
}


// ¸ßÁÁ¹Ø¼ü×Ö
void Highlight::run(State state, const string& str, const Command* pCmd, const Syntax* pKey)
{
	switch(state)
	{
	case State::COMMAND:
		if(pCmd == nullptr)
			break;
		attribute::set(color.command.fore);
		attribute::set(color.command.mode);
		break;

	case State::KEY:
		if(pKey == nullptr)
			break;
		attribute::set(color.key.fore);
		attribute::set(color.key.mode);
		break;

	case State::DELIM:
		attribute::set(color.delim.fore);
		attribute::set(color.delim.mode);
		printf(":");
		attribute::rest();
		return;
	}
	for(size_t i = 0; i < str.size(); i++)
		printf("\b \b");
	printf("%s", str.c_str());
	attribute::rest();
}


void Highlight::setCommandFore(attribute::fore attr)
{
	color.command.fore = attr;
}

void Highlight::setCommandMode(attribute::mode attr)
{
	color.command.mode = attr;
}

void Highlight::setKeyFore(attribute::fore attr)
{
	color.key.fore = attr;
}

void Highlight::setKeyMode(attribute::mode attr)
{
	color.key.mode = attr;
}

void Highlight::setDelimFore(attribute::fore attr)
{
	color.delim.fore = attr;
}

void Highlight::setDelimMode(attribute::mode attr)
{
	color.delim.mode = attr;
}
