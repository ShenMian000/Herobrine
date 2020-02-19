// Copyright 2019 SMS
// License(Apache-2.0)
// √¸¡Ó––

#ifndef HIMCONSOLE_H_
#define HIMCONSOLE_H_

#include "console/Console.h"
#include "Session.h"



typedef ulong slave_id_t;

class Himconsole : public Console
{
public:
	Himconsole();
	~Himconsole();

	const Session_& getSlave();

private:
	map<slave_id_t, Session_*> slave;
};



#endif // HIMCONSOLE_H_
