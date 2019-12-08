// Copyright 2019 SMS
// License(Apache-2.0)
// ���ض�

#include "slave.h"



// װ��ģ��
bool Slave::Load(const string& path)
{
	// ���ģ���Ƿ���װ��
	if(any_of(module.begin(), module.end(), [path](module_info* mod){return mod->path == path;}))
	{
		print::error("ģ����װ��");
		return false;
	}

	// ���ģ���Ƿ����

	return true;
}

// ж��ģ��
bool Slave::Unload(const string& path)
{
	// ���ģ���Ƿ���װ��
	if(none_of(module.begin(), module.end(), [path](module_info* mod){return mod->path == path;}))
	{
		print::error("ģ��δװ��");
		return false;
	}

	return true;
}


void Slave::OnAccept()
{
	print::info("�����ӽ���");

	// ����Ŀ�������Ϣ
	char* pBuf = new char[sizeof(os_info)+sizeof(user_info)];

	memset(pBuf, '\0', sizeof(*pBuf));
	memcpy(pBuf, &os_info, sizeof(os_info));
	pBuf += sizeof(os_info);
	memcpy(pBuf, &user_info, sizeof(user_info));

	delete[] pBuf;
}
