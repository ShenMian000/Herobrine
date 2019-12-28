// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HistoryCommand : public Command
{
public:
	HistoryCommand()
		: Command("history", "显示命令历史纪录", "Herobrine")
	{
	}

	void excute(Console& console) override
	{
	}
};


