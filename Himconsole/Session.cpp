// Copyright 2019 SMS
// License(Apache-2.0)
// ���ض�

#include "Session.h"
#include "Server.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using std::string;
using namespace boost;



Session::Session(asio::io_service& ios)
		: sock(ios)
{
}


// ��������
void Session::send(const string& buf)
{
	//asio::async_write(sock, asio::buffer(buf),
	//	boost::bind(&Session::OnSend, this, asio::placeholders::error));
}

// �ص�: ������ɺ�
void Session::OnSend()
{
}


// ��������
void Session::recv(string& buf)
{
	//asio::async_read(sock, asio::buffer(buf),
	//	boost::bind(&Session::OnRecv, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
}

// �ص�: ���Խ���ʱ
void Session::OnRecv()
{
}


// ��ȡ IP��ַ
const string& Session::ipAddress() const
{
	return sock.remote_endpoint().address().to_string();
}

// ��ȡ �˿�
ushort Session::port() const
{
	return sock.remote_endpoint().port();
}


// ���»�����Ϣ
void Session::update()
{
}















/*
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
	char* pBuf = new char[sizeof(osInfo)+sizeof(userInfo)];

	memset(pBuf, '\0', sizeof(*pBuf));
	memcpy(pBuf, &osInfo, sizeof(osInfo));
	pBuf += sizeof(osInfo);
	memcpy(pBuf, &userInfo, sizeof(userInfo));

	delete[] pBuf;
}
*/
