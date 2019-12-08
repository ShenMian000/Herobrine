// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class History : public Command
{
public:
	History()
		: Command("history", "显示命令历史纪录", "Herobrine")
	{
	}

	void excute()
	{
	}
};


