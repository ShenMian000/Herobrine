// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HistoryCommand : public Command
{
public:
	HistoryCommand()
		: Command("显示命令历史纪录", "Herobrine")
	{
	}

	void excute(Console& console) override
	{
		auto size = console.getHistorySize();

		for(size_t i = 0; i < size; i++)
		{
			if(console.getHistory(i).empty())
				break;

			printf("%3zu %s\n", i, console.getHistory(i).c_str());
		}
	}
};


