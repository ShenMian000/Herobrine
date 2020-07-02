// Copyright 2020 SMS
// License(Apache-2.0)

#include <string>
#include <unordered_map>

class Console;

class Command
{
	struct Syntax;

public:
	virtual void execute(Console&);
	
	void insertSyntax(const std::string&, const Syntax&);

	const std::string& getDescription() const;
	const std::string& getAuthor() const;

private:
	const std::string desc;
	const std::string author;

	void (*func)(Console&);
	
	std::unordered_map<std::string, Syntax> syntax;
};
