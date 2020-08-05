// Copyright 2020 SMS
// License(Apache-2.0)
// 服务定位器模式

#include "service_locator.h"

using std::string;

void ServiceLocator::addService(const string& id, Service* s)
{
	if(services.find(id) != services.end())
		throw std::invalid_argument("ID already exists");

	services.insert({id, s});
}

template <class T>
T* ServiceLocator::getService(const string& id)
{
	auto s = services.find(id);

	if(s == services.end())
		throw std::invalid_argument("ID does not exist");

	return dynamic_cast<T*>(s->second);
}


Service::~Service()
{
}
