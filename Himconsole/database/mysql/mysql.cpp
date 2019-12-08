// Copyright 2019 SMS
// License(Apache-2.0)
// MySQL数据库

/*

#include "mysql.h"



namespace database
{

namespace mysql
{

Mysql::Mysql(const string& host, const string& user, const string& passwd, const string& db, port_t port)
	: host_(host), user_(user), passwd_(passwd), db_(db), port_(port)
{
	hConnect_ = mysql_init(nullptr);
}


// 连接数据库
bool Mysql::open()
{
	auto ret = mysql_real_connect(hConnect_, host_.c_str(), user_.c_str(), passwd_.c_str(), db_.c_str(), port_, nullptr, 0);
	
	if(!ret)
	{
	}

	status_ = true;

	return true;
}

// 关闭数据库连接
void Mysql::close()
{
	if(status_ == false)
		return;
	
	status_ = false;
	mysql_close(hConnect_);
}

MYSQL_RES* Mysql::query(const string& sql)
{
	mutex_.lock();

	mysql_real_query(hConnect_, sql.c_str(), sql.size());

	mutex_.unlock();
	
	return mysql_store_result(hConnect_);
}

} // namespace mysql

} // namespace database

*/
