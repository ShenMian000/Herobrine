// Copyright 2019 SMS
// License(Apache-2.0)
// Author: SMS
// 

#ifndef SOCKET_INCLUDE_H_
#define SOCKET_INCLUDE_H_


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
	#define OS_WIN    // Windows
	#ifdef _WIN64
		#define OS_WIN64
	#else
		#define OS_WIN32
	#endif
#else
	#define OS_LINUX  // Linux
	#define INADDR_ANY  (ULONG)0x00000000
	#define INADDR_NONE 0xffffffff
#endif


// 定义操作系统宏, 用于判断操作系统
#ifdef OS_LINUX
	#ifdef MAXOSX
		#define OS_MACOSX	// Mac OS X
	#endif
#endif


// Windows 通用头文件
#ifdef OS_WIN
	#include <winsock2.h>
#endif


// Linux 通用头文件
#ifdef OS_LINUX
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif


// 通用定义
const int error = -1;
typedef ushort port_t;


// Windows 通用定义
#ifdef OS_WIN
	#ifndef uint64_t
		typedef unsigned __int64 uint64_t;
	#endif
	#ifndef int64_t
		typedef __int64 int64_t;
	#endif

	typedef int64_t socket_t;

	const socket_t invalide_socket = ~0;
	const auto     inaddr_none		 = 0xffffffff;

	#define Errno       WSAGetLastError()
	#define closesocket ::closesocket
#endif
	

// Linux 通用定义
#ifdef OS_LINUX
	typedef int socket_t;

	const socket_t invalide_socket = -1;

	#define Errno       errno
	#define closesocket ::close
#endif


#endif	// SOCKET_INCLUDE_H_
