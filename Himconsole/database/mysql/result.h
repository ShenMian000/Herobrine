// Copyright 2019 SMS
// License(Apache-2.0)
// MySQL½á¹û¼¯

/*

#ifndef DATABASE_MYSQL_RESULT_H_
#define DATABASE_MYSQL_RESULT_H_

#include "mysql.h"



namespace database
{

namespace mysql
{

class Result
{
public:
	Result();
	~Result();

	void operator=(MYSQL_RES*);

	bool fetchRow();

	const char* getString(int index);
	const char* getString(const string& field);

	int getInt(int index);
	int getInt(const string& field);

private:
	MYSQL_RES* result_;
	MYSQL_ROW  row_;

	int GetIndexByField(const string& field);
};

} // namespace mysql

} // namespace database



#endif // DATABASE_MYSQL_RESULT_H_

*/
