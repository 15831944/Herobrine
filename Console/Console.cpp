// Copyright 2019 SMS
// License(Apache-2.0)

/*
 ����ģʽ
 �̲߳���ȫ
 */

#include "Console.h"
#include <assert.h>

#include <conio.h>

using std::string;

// ����״̬
// ��ǰ�������������
enum class InputState
{
	Command,
	Key,
	String,
	Integer,
	Floating
};

// ����ʹ�����
enum class QuotationMark
{
	None,
	Single,
	Double
};



Console* Console::instance = nullptr;


Console::Console()
{
}


Console& Console::getInstance()
{
	if(instance == nullptr)
		instance = new Console();
	return *instance;
}


// ����������
void Console::run()
{
	while(true)
	{
		InputState		state					= InputState::Command;
		QuotationMark quotationMark = QuotationMark::None;

		printf(prompt.c_str());

		while(true)
		{
			char c = getch();

			switch(state)
			{
			case InputState::Command:
				break;

			case InputState::Key:
				break;

			case InputState::String:
				break;

			case InputState::Integer:
				break;

			case InputState::Floating:
				break;
			}
		}
	}
}


// �������
//   name : Ҫ��ӵ���������
//   cmd  : Ҫ��ӵ������ָ��
void Console::addCommand(const std::string& name, Command* cmd)
{
	// ����������
	assert(cmd != nullptr);

	commands.insert({name, cmd});
}


// ����������ʾ��
//   prompt : Ҫ���õ�������ʾ��
void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}
