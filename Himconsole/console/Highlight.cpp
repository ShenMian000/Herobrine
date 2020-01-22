// Copyright 2019 SMS
// License(Apache-2.0)
// ¸ßÁÁ

#include "Highlight.h"
#include "Console.h"



Highlight::Highlight()
		: console(nullptr)
{
	color.command.fore = Attribute::Fore::green;
	color.command.mode = Attribute::Mode::fore_bold;
	color.key.fore		 = Attribute::Fore::yellow;
	color.key.mode		 = Attribute::Mode::fore_bold;
	color.delim.fore	 = Attribute::Fore::white;
	color.delim.mode	 = Attribute::Mode::fore_bold;
}

Highlight::Highlight(Console* console)
		: console(console)
{
	color.command.fore = Attribute::Fore::green;
	color.command.mode = Attribute::Mode::fore_bold;
	color.key.fore		 = Attribute::Fore::yellow;
	color.key.mode		 = Attribute::Mode::fore_bold;
	color.delim.fore	 = Attribute::Fore::white;
	color.delim.mode	 = Attribute::Mode::fore_bold;
}


// ¸ßÁÁ¹Ø¼ü×Ö
void Highlight::run()
{
	switch(console->state)
	{
	case State::COMMAND:
		if(console->pCommand == nullptr)
			break;
		Attribute::set(color.command.fore);
		Attribute::set(color.command.mode);
		break;

	case State::KEY:
		if(console->pKey == nullptr)
			break;
		Attribute::set(color.key.fore);
		Attribute::set(color.key.mode);
		break;

	case State::DELIM:
		Attribute::set(color.delim.fore);
		Attribute::set(color.delim.mode);
		printf(":");
		Attribute::rest();
		return;
	}
	for(size_t i = 0; i < console->buf.size(); i++)
		printf("\b \b");
	printf("%s", console->buf.c_str());
	Attribute::rest();
}


void Highlight::setCommandFore(Attribute::Fore attr)
{
	color.command.fore = attr;
}

void Highlight::setCommandMode(Attribute::Mode attr)
{
	color.command.mode = attr;
}

void Highlight::setKeyFore(Attribute::Fore attr)
{
	color.key.fore = attr;
}

void Highlight::setKeyMode(Attribute::Mode attr)
{
	color.key.mode = attr;
}

void Highlight::setDelimFore(Attribute::Fore attr)
{
	color.delim.fore = attr;
}

void Highlight::setDelimMode(Attribute::Mode attr)
{
	color.delim.mode = attr;
}
