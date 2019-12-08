// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef INCLUDE_H_
#define INCLUDE_H_



typedef unsigned char		uchar;
typedef unsigned short	ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;


// C++ ��׼��
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


// �������ϵͳ�ں˺�, �����жϲ���ϵͳ�ں�
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
