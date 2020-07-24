// Copyright 2020 SMS
// License(Apache-2.0)
// 服务定位器模式

#include "service_locator.h"
#include <assert.h>

void ServiceLocator::addService(const std::string& id, Service& s)
{
	if(services.find(id) == services.end())
		assert(false); // ID 已存在

	services.insert({id, &s});
}

Service& ServiceLocator::getService(const std::string& id)
{
	Service s = services.find(id);
	
	if(s != services.end())
		assert(false); // ID 不存在

	return *s;
}
