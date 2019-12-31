
#include "command.h"
#include "include.h"
#include <conio.h>
#include <iostream>
#include <stdio.h>



map<string, string> args;

#define DEBUG_
#ifdef DEBUG

int main()
{
	string buffer;
	size_t pos = 0;

	string key, value;

	Argument			 arg;
	Argument::Type type;

	bool inputValue	 = false; // 正在输入值
	bool inputString = false; // 正在输入字符串

	while(true)
	{
		char buf = _getch();

		switch(buf)
		{
		case ' ':
			if(inputString)
				break;
		case '\r':
			if(inputValue)
			{
				value = buffer.substr(pos);
				if()
					arg.Long = stol(value);
				else
					arg.String = value;
			}
			break;

		case '"':
			if(!inputValue)
				continue;

			if(!inputString)
			{
				// 检查key对应的类型是不是string
				inputString = true;
			}
			else
			{
				arg.String = buffer.substr(pos);
				args.insert({key, arg});
				inputString = false;
			}
			break;

		case ':':
			key				 = buffer.substr(pos);
			pos				 = buffer.size();
			inputValue = true;
			break;
		}

		printf("%c", buf);

		if(buf == '\r')
			break;

		buffer += buf;
	}

	getchar();
	getchar();
	return 0;
}

#endif
