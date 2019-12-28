// Copyright 2019 SMS
// License(Apache-2.0)
// ������

// ����һ����ͨ�����иþ߱��Ĺ���
// Himconsole�������Ĺ���, ����ģ��API GetSessionInfo...

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "include.h"
#include "command.h"
#include "print.h"



enum class Type
{
	Int,     // ����
	Short,   // ������
	Long,    // ������
	String,  // �ַ���
};

struct arg
{
	Type  type;
	void* value;
};


class Console
{
public:
	Console();
	virtual ~Console();

	size_t        getArgSize();          // ��ȡ��������
	const string& getArg(const string&); // ��ȡ����

	void setPrompt(const string&);

	void          setHistorySize(size_t);
	const string& getHistory(size_t);
	size_t        getHistorySize();

	void     addCommand(Command*);
	void     delCommand(Command*);
	Command* getCommand(size_t);
	size_t   getCommandSize();

	void console();

private:
	map<string, string> args;
	vector<Command*>    command;
	deque<string>       history;           // ������ʷ��¼
	size_t              historySize = 30;  // ���������ʷ��¼����
	string              prompt;            // ��������ʾ��

	string ReadLine();
	void   SplitCmdToArg(const string& cmd);
	bool   CheckSyntax();
	inline  int  Input();                  // ����һ���ַ�, ������
	virtual void PrintPrompt();
};



#endif // CONSOLE_H_
