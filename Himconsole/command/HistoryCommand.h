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
		auto& history = console.getHistory();

		size_t i = 1;

		for(auto& h : history)
		{
			if(h.empty())
				break;
			printf("%3zu %s\n", i++, h.c_str());
		}
	}
};
