// Copyright 2019 SMS
// License(Apache-2.0)

#include "../console/Command.h"
#include "../print.h"



class ListenCommand : public Command
{
public:
	ListenCommand()
			: Command("监听", "Herobrine", Platform::Common, License::Apache_2_0)
	{
		addSyntax("ip", {Syntax::Type::STRING, "监听的IP地址", false});
		addSyntax("port", {Syntax::Type::INT, "监听的端口地址", false});
	}

	void excute(Console& c) override
	{
		print::good("监听开始: " + c.getStringArg("ip") + ":" + c.getStringArg("port"));
	};
};


