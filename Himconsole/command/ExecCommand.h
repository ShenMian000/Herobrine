// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"
#include "../print.h"



class ExecCommand : public Command
{
public:
	ExecCommand()
		: Command("exec", "执行外部系统命令", "Herobrine")
	{
		syntax.push_back({"command", Argument::Type::String});
	}

	void excute(Console& console) override
	{
		char	buf[1024];
		FILE* pipe;
			
		pipe = _popen(console.getStringArg("command").c_str(), "r");

		if(pipe == NULL)
		{
			print::error("无法打开管道");
			return;
		}

		while(!feof(pipe))
			if(fgets(buf, 1024, pipe))
				printf("%s", buf);

		if(_pclose(pipe) == -1)
		{
			print::error("无法关闭管道");
			return;
		}
	}
};


