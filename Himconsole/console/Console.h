// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../include.h"
#include "../print.h"
#include "command.h"
#include "AutoComplete.h"
#include "Highlight.h"



class Console
{
	friend class AutoComplete;
	friend class Highlight;

public:
	Console();
	virtual ~Console();

	void run();

	const std::string& getStringArg(const std::string& key) const;
	int								 getIntArg(const std::string& key) const;
	long							 getLongArg(const std::string& key) const;
	size_t						 getArgSize() const;

	void setHistorySize(size_t);
	void addHistory(const vector<std::string>&) const;

	void		 addCommand(const std::string& name, Command*);
	void		 delCommand(const std::string& name);
	Command* getCommand(const std::string& name) const;

	void setPrompt(const std::string&);

	const map<std::string, Command*>& getCommand() const;
	const deque<std::string>&					getHistory() const;

private:
	map<std::string, std::string> args; // ����
	map<std::string, Command*>		commands;
	deque<std::string>						historys;					// ������ʷ��¼
	size_t												historySize = 30; // ���������ʷ��¼����
	std::string										prompt;						// ��������ʾ��
	AutoComplete									autoComplete;
	Highlight											highlight;

	string												buf;


	Command* pCommand = nullptr;
	Syntax*	 pKey			= nullptr;

	virtual void PrintPrompt();
	inline int	 GetChar(); // ����һ���ַ�, ������
	Syntax*			 getKey(const std::string& name) const;

	// ����״̬, ��ǰ������Ĳ���
	enum class State
	{
		COMMAND, // ��������
		KEY,		 // �����
		DELIM,   // ����ָ���
		VALUE		 // ����ֵ
	} state;
};



#endif // CONSOLE_H_
