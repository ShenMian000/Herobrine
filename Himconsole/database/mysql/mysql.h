// Copyright 2019 SMS
// License(Apache-2.0)
// MySQL连接

/*

#ifndef DATABASE_MYSQL_MYSQL_H_
#define DATABASE_MYSQL_MYSQL_H_

#include <mysql/mysql.h>
#include "../../include.h"
#include "../../socket/include.h"



namespace database
{

namespace mysql
{

class Mysql
{
public:
	Mysql();
	Mysql(const string& host, const string& user, const string& passwd, const string& db, port_t port = 3306);
	~Mysql();

	bool open();
	bool open(const string& host, const string& user, const string& passwd, const string& db, port_t port = 3306);
	void close();

	MYSQL_RES* query(const string& sql);

private:
	MYSQL* hConnect_;

	bool   status_ = false; // 数据库连接状态
	string host_;
	string user_;
	string passwd_;
	string db_;
	port_t port_;

	mutex  mutex_;
};

} // namespace mysql

} // namespace database



#endif // DATABASE_MYSQL_MYSQL_H_


*/
