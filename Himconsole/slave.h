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
typedef struct
{
	os_type type;
} os_info;


// Ŀ���û�������Ϣ
typedef struct
{
	char* name; // �û�����
} user_info;


// ģ����Ϣ
typedef struct
{
	char*	path;     // ·��
	char* auther;   // ����
	char* license;  // ���֤
} module_info;


class Slave
{
public:
	Slave();
	~Slave();

	bool Load(const string& mod);   // װ��ģ��
	bool Unload(const string& mod); // ж��ģ��

private:
	os_info   os_info;                 // ϵͳ��Ϣ
	user_info user_info;               // �û���Ϣ
	forward_list<module_info*> module; // ��װ�ص�ģ��

	void OnAccept();
};



#endif // SLAVE_H_
