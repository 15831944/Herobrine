// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef COMMAND_H_
#define COMMAND_H_

#include "include.h"



// ����ƽ̨
enum class Platform
{
	Common,
	Windows_XP,
	Windows_10,
};

// ��ԴЭ������
enum class License
{
	Apache_2_0,
	BSD,
	GPL_3_0,
	MPL_2_0,
	LGPL_3_0,
	TIM,
};


class Console;


class Command
{
public:
	Command(
		const string& name,
		const string& desc,
		const string& author,
		Platform      platform = Platform::Common,
		License       license  = License::Apache_2_0
	);
	virtual ~Command();

	const string& getName();
	const string& getDescription();
	const string& getAuthor();
	/*
	Platform      getPlatform();
	License       getLicense();
	const string& getPlatform();
	*/

	bool checkSyntax(Console&);
	virtual void excute(Console&) = 0;  // ִ������

protected:
	string   name;
	string   desc;
	string   author;
	Platform platform;
	License  license;
	map<string, string> syntax;         // �﷨��ʽ name-type-value
};



#endif // COMMAND_H_
