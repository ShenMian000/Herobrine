// Copyright 2020 SMS
// License(Apache-2.0)

#include <string>
#include <unordered_map>

class Console
{
public:
	void execute(const std::string& cmd);

	const std::string& getStringArg(const std::string& key);

private:
	std::unordered_map<std::string, std::string> args;
};
