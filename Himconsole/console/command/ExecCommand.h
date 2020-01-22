// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"
#include "../../print.h"



#ifdef OS_WIN
#define popen  _popen
#define pclose _pclose
#elif OS_LINUX
#define popen  popen
#define pclose pclose
#endif


class ExecCommand : public Command
{
public:
	ExecCommand()
		: Command("执行外部系统命令", "Herobrine")
	{
		addSyntax("command", {Syntax::Type::STRING, "要执行的命令", false});
	}

	void excute(Console& console) override
	{
		char	buf[1024];
		FILE* pipe;
			
		pipe = popen(console.getStringArg("command").c_str(), "r");

		if(pipe == NULL)
			throw "无法打开管道";

		while(!feof(pipe))
			if(fgets(buf, 1024, pipe))
				printf("%s", buf);

		if(pclose(pipe) == -1)
			throw "无法关闭管道";
	}
};


