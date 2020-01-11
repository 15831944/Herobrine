// Copyright 2019 SMS
// License(Apache-2.0)
// ������

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

	const string& getStringArg(const string& key);
	int           getIntArg(const string& key);
	long          getLongArg(const string& key);
	size_t        getArgSize();

	void setHistorySize(size_t);
	void addHistory();

	void		 addCommand(const string& name, Command*);
	void		 delCommand(const string& name);
	Command* getCommand(const string& name);

	const map<string, Command*>& getCommand();
	const deque<string>&				 getHistory();

	void          setPrompt(const string&);

	void run();

private:
	map<string, string>   args;             // ����
	map<string, Command*> commands;
	deque<string>				  historys;					// ������ʷ��¼
	size_t							  historySize = 30; // ���������ʷ��¼����
	string							  prompt;						// ��������ʾ��

	virtual void PrintPrompt();
	inline  int  GetChar();                   // ����һ���ַ�, ������
};



#endif // CONSOLE_H_
