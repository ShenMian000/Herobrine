// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
		: Command("help", "ÏÔÊ¾ÃüÁî°ïÖúĞÅÏ¢", "Herobrine")
	{
	}

	void excute(Console& console) override
	{
	}
};


