// Copyright 2019 SMS
// License(Apache-2.0)
// 

#ifndef COMMAND_H_
#define COMMAND_H_

#include "../include.h"



class  Console;

// 运行平台
enum class Platform
{
	Common,
	Windows_XP,
	Windows_10,
};

// 开源协议类型
enum class License
{
	Apache_2_0,
	BSD_2_Clause,
	BSD_3_Clause,
	GPL_3_0,
	LGPL_3_0,
	MPL_2_0,
	TIM
};

// 语法
struct Syntax
{
	enum class Type
	{
		INT,	  // 整型 int
		LONG,   // 长整型 long
		FLOAT,  // 单精度浮点数 float
		DOUBLE, // 双精度浮点数 double
		BOOL,   // 布尔值 bool
		STRING, // 字符串 std::string
		OPTION  // 选项
	};
	
	Syntax(Type type, const string& desc, bool required = true, Syntax* required_next = nullptr, Syntax* show_next = nullptr)
			: type(type), desc(desc), required(required), required_next(required_next), show_next(show_next)
	{
	}

	Syntax()
			: type(Type::OPTION), required(true), required_next(nullptr), show_next(nullptr)
	{
	}

	Type		type;
	string  desc;
	bool		required;
	Syntax* required_next;
	Syntax* show_next;
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

	const string& getDescription() const;
	const string& getAuthor() const;
	Platform			getPlatform() const;
	License				getLicense() const;

	const map<const string, const Syntax>& getSyntax() const;

protected:
	void addSyntax(const string&, const Syntax);

private:
	const string	 desc;
	const string	 author;
	const Platform platform;
	const License	 license;

	map<const string, const Syntax> syntax;
	map<const string, const string> str;

	virtual void excute(Console&) = 0;
};



#endif // COMMAND_H_
