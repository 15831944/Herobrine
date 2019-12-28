// Copyright 2019 SMS
// License(Apache-2.0)
// ���ض�

#ifndef SLAVE_H_
#define SLAVE_H_

#include "include.h"
#include "print.h"



enum class os_type
{
	windows_xp,
	windows_10,
	kali,
};
	

// Ŀ�����ϵͳ������Ϣ
struct os_info_
{
	os_type type;
};


// Ŀ���û�������Ϣ
struct user_info_
{
	char* name; // �û�����
};


// ģ����Ϣ
struct module_info
{
	char*	path;     // ·��
	char* auther;   // ����
	char* license;  // ���֤
};


class Slave
{
public:
	Slave();

	bool Load(const string& mod);      // װ��ģ��
	bool Unload(const string& mod);    // ж��ģ��

private:
	os_info_   osInfo;                 // ϵͳ��Ϣ
	user_info_ userInfo;               // �û���Ϣ
	forward_list<module_info*> module; // ��װ�ص�ģ��

	void OnAccept();
};



#endif // SLAVE_H_
