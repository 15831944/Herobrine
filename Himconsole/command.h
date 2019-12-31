// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef COMMAND_H_
#define COMMAND_H_

#include "include.h"



class  Console;

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

// �﷨
struct Syntax
{
	enum class Type
	{
		INT,	  // ���� int
		LONG,   // ������ long
		FLOAT,  // �����ȸ����� float
		DOUBLE, // ˫���ȸ����� double
		BOOL,   // ����ֵ bool
		STRING, // �ַ��� std::string
		OPTION  // ѡ��
	};
	
	Syntax(Type type, const string& desc, bool required = true, Syntax* compliance = nullptr)
		: type(type), desc(desc), required(required), compliance(compliance)
	{
	}

	Syntax()
		: type(Type::OPTION), required(true), compliance(nullptr)
	{
	}

	Type		type;
	string  desc;
	bool		required;
	Syntax* compliance;
};


class Command
{
	friend class Console;

public:
	Command(
		const string& desc,
		const string& author,
		Platform      platform = Platform::Common,
		License       license  = License::Apache_2_0);
	virtual ~Command();

	const string& getDescription();
	const string& getAuthor();
	Platform      getPlatform();
	License       getLicense();

protected:
	map<string, Syntax> syntax;

private:
	const string	 desc;
	const string	 author;
	const Platform platform;
	const License	 license;

	virtual void excute(Console&) = 0;
};



#endif // COMMAND_H_
