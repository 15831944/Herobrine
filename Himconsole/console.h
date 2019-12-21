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



class Console
{
public:
	Console();
	virtual ~Console();

	size_t        getArgSize();          // ��ȡ��������
	const string& getArg(const string&); // ��ȡ����

	void setPrompt(const string&);
	void setHistorySize(size_t);

	void addCommand(Command*);

	void console();

private:
	map<string, string> arg;
	vector<Command*>    command;
	deque<string>       history;           // ������ʷ��¼
	size_t              historySize = 10;  // ���������ʷ��¼����
	string              prompt;            // ��������ʾ��

	string ReadLine();
	void   SplitCmdToArg(const string& cmd);
	bool   CheckSyntax();
	virtual void PrintPrompt();
};



#endif // CONSOLE_H_
