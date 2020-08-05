// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef PRINT_SERVICE_H_
#define PRINT_SERVICE_H_

#include <string>
#include <mutex>
#include "service_locator.h"

class Print : public Service
{
public:
	Print(std::mutex&);

	void info(const std::string&);
	void good(const std::string&);
	void error(const std::string&);
	void warn(const std::string&);

private:
	std::mutex& mutex;
};

#endif // PRINT_SERVICE_H_
