// Copyright 2019 SMS
// License(Apache-2.0)

#include "command.h"

#ifndef MODULE_H_
#define MODULE_H_



class Slave;

class Module : public Command
{
public:
	virtual void execute(Slave&) = 0;

	static void loadModuleInDir(const string&);

private:
};


#endif
