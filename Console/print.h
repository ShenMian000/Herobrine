// Copyright 2020 SMS
// License(Apache-2.0)
//

#ifndef PRINT_H_
#define PRINT_H_

#include <string>
#include <mutex>



class Print
{
public:
	static void info(const std::string&);
	static void good(const std::string&);
	static void error(const std::string&);
	static void warn(const std::string&);

private:
	static std::mutex mutex;
};



#endif // PRINT_H_
