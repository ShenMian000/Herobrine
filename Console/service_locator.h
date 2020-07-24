// Copyright 2020 SMS
// License(Apache-2.0)
// 服务定位器模式

#ifndef SERVICE_LOCATOR_H_
#define SERVICE_LOCATOR_H_

#include <string>
#include <map>

class Service;

class ServiceLocator
{
public:
	void     addService(const std::string&, Service&);
	Service& getService(const std::string&);

private:
	std::map<std::string, Service*> services;
};

class Service
{
};

#endif // SERVICE_LOCATOR_H_
