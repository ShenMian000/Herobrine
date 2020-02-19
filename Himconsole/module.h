// Copyright 2019 SMS
// License(Apache-2.0)

#include "console/command.h"

#ifndef MODULE_H_
#define MODULE_H_



class Session_;

class Module : public Command
{
public:
	virtual void execute(Session_&) = 0;

	static void loadModuleInDir(const string&);

private:
};


#endif
