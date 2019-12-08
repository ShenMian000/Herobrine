// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef INCLUDE_H_
#define INCLUDE_H_



typedef unsigned char		uchar;
typedef unsigned short	ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;


// C++ 标准库
#include <thread>
using std::thread;


// C++ STL
#include <string>
using std::string;
using std::to_string;
using std::stoi;

#include <vector>
using std::vector;

#include <deque>
using std::deque;

#include <forward_list>
using std::forward_list;

#include <list>
using std::list;


// 定义操作系统内核宏, 用于判断操作系统内核
#ifdef _WIN32
	#define OS_WIN		// Windows
	#ifdef _WIN64
		#define OS_WIN64
	#else
		#define OS_WIN32
	#endif
#else
	#define OS_LINUX	// Linux
#endif



#endif // INCLUDE_H_
