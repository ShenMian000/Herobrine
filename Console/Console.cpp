// Copyright 2019 SMS
// License(Apache-2.0)

#include "console.h"
#include "command.h"
#include <assert.h>

#include <conio.h>

using std::string;



// 输入状态
// 当前正在输入的内容
enum class InputState
{
	Command,
	Key,
	Value
};

// 引号使用情况
enum class QuotationMark
{
	None,
	Single,
	Double
};



// 开启命令行
void Console::run()
{
	while(true)
	{
		string					 buf;
		Command*				 pCommand			 = nullptr;
		Command::Syntax* pSyntax			 = nullptr;
		InputState			 state				 = InputState::Command;
		QuotationMark		 quotationMark = QuotationMark::None;

		printf(prompt.c_str());

		while(true)
		{
			char c = _getch();

			// 结束输入
			if(c == '\r' || c == '\n')
			{
				// 验证语句是否是正确的
				switch(state)
				{
				case InputState::Command:
					// 检查命令是否存在
					break;

				case InputState::Key:
					// 检查Key是否为Option类型
					break;

				case InputState::Value:
					// 检查字符串中的引号是否配对
					break;
				}
			}

			/*
			if(c == '\r' || c == '\n')
				if(state == InputState::Command ||
					 state == InputState::Key && buf.size() == 0)
				{
					// 检查参数是否填写完整
				}
				else
					continue;
			*/

			// 过滤非法字符
			if(!isprint(c))
				continue;

			// 根据具体情况过滤非法字符
			switch(state)
			{
			case InputState::Command:
				// 是否存在可能的命令
				break;

			case InputState::Key:
				// 是否存在可能的键
				break;

			case InputState::Value:
				// 根据Key的类型进行判断
				switch(pSyntax->type)
				{
				case Command::Syntax::Type::Int:
					break;

				case Command::Syntax::Type::Float:
					break;

				case Command::Syntax::Type::String:
					break;
				}
				break;
			}

			/*
			switch(state)
			{
			case InputState::Command:
					break;

				case InputState::Key:
					break;

				case InputState::Value:
					switch(pSyntax->type)
					{
					case Command::Syntax::Type::String:
						switch(quotationMark)
						{
						case QuotationMark::None:
							if(c == '\'')
								quotationMark = QuotationMark::Single;
							else if(c == '\"')
								quotationMark = QuotationMark::Double;
							buf += c;
							break;

						case QuotationMark::Single:
							if(c != '\'')
								continue;
							quotationMark = QuotationMark::None;
							state					= InputState::Key;
							break;

						case QuotationMark::Double:
							if(c != '\"')
								continue;
							quotationMark = QuotationMark::None;
							state					= InputState::Key;
							break;
						}
						break;

					case Command::Syntax::Type::Int:
						break;

					case Command::Syntax::Type::Float:
						break;
					}
				}

				printf("%c", c);
			}
			*/

			// 执行命令
			assert(pCommand != nullptr);
			try
			{
			}
			catch(...)
			{
			}
		}
	}
}


// 添加命令
//   name : 要添加的命令名称
//   cmd  : 要添加的命令的指针
void Console::addCommand(const std::string& name, Command* cmd)
{
	// 不存在名称
	assert(cmd != nullptr);

	commands.insert({name, cmd});
}


// 设置命令提示符
//   prompt : 要设置的命令提示符
void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}
