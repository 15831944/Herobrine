// Copyright 2019 SMS
// License(Apache-2.0)
//

#include "Server.h"
#include "slave.h"
#include <boost/bind.hpp>
#include "print.h"

using namespace boost;



Server::Server(ushort port)
		: acceptor(ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
	ios.run();
}


// ��ʼ
void Server::run()
{
	Listen();
}


// �����ӽ���ʱ�ص�
void Server::OnAccept(const system::error_code& err, socket_ptr sock)
{
	if(err)
		return;

	Print::good("�¿ͻ��˽���");

	// ����¿ͻ���
	Slave slave(*sock);

	Listen();
}


// �첽����
void Server::Listen()
{
	socket_ptr sock(new asio::ip::tcp::socket(ios));
	acceptor.async_accept(*sock, boost::bind(&Server::OnAccept, this, asio::placeholders::error, sock));
}
