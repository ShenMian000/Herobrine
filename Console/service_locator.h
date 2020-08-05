// Copyright 2020 SMS
// License(Apache-2.0)
// 服务定位器模式

#ifndef SERVICE_LOCATOR_H_
#define SERVICE_LOCATOR_H_

#include <assert.h>
#include <string>
#include <map>
#include <stdexcept>

using std::string;
using std::string;

class Service
{
public:
	virtual ~Service();
};

class ServiceLocator
{
public:
	void addService(const std::string&, Service*);
	template <class T> T* getService(const std::string&);

private:
	std::map<std::string, Service*> services;
};

#endif // SERVICE_LOCATOR_H_
