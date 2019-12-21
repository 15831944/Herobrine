// Copyright 2019 SMS
// License(Apache-2.0)
// �޸Ŀ���̨��������

#include "attribute.h"



#ifdef OS_WIN

HANDLE hStdOut_;  // ��׼������
WORD   defAttr_;  // Ĭ������

WORD   attr_;     // ��ǰ����̨�ַ�����ֵ


// ����ǰ������
void ConsoleOutAttribute(fore attr)
{
	attr_ &= 0xf0;
	attr_ |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut_, attr_);
}


// ���ñ�������
void ConsoleOutAttribute(back attr)
{
	attr_ &= 0x0f;
	attr_ |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut_, attr_);
}


// ���ù�ͬ����
void ConsoleOutAttribute(mode attr)
{
	attr_ |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut_, attr_);
}


// ��ԭ��Ĭ������
void ConsoleOutAttributeRest()
{
	attr_ = defAttr_;
	SetConsoleTextAttribute(hStdOut_, attr_);
}


// �Զ���ʼ��
class WinAttributeInit
{
public:
	WinAttributeInit()
	{
		hStdOut_ = GetStdHandle(STD_OUTPUT_HANDLE);

		// ��ȡ��ǰ�������ַ�����
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(hStdOut_, &bufInfo);
		defAttr_ = bufInfo.wAttributes;
		attr_    = defAttr_;
	}

	~WinAttributeInit()
	{
	}
};

WinAttributeInit winAttributeInit;

#endif // OS_WIN



#ifdef OS_LINUX

// ����ǰ������
void ConsoleOutAttribute(fore attr)
{
	switch(attr)
	{
	case fore::black:
		printf("\033[30m");
		break;

	case fore::blue:
		printf("\033[34m");
		break;

	case fore::cyan:
		printf("\033[36m");
		break;

	case fore::gray:
		printf("");
		break;

	case fore::green:
		printf("\033[32m");
		break;

	case fore::purple:
		printf("\033[35m");
		break;

	case fore::red:
		printf("\033[31m");
		break;

	case fore::white:
		printf("\033[37m");
		break;

	case fore::yellow:
		printf("\033[33m");
		break;
	}
}


// ���ñ�������
void ConsoleOutAttribute(back attr)
{
	switch(attr)
	{
	case back::black:
		printf("\033[40;");
		break;

	case back::blue:
		printf("\033[34;");
		break;

	case back::cyan:
		printf("\033[36;");
		break;

	case back::gray:
		printf("");
		break;

	case back::green:
		printf("\033[32;");
		break;

	case back::purple:
		printf("\033[35;");
		break;

	case back::red:
		printf("\033[31;");
		break;

	case back::white:
		printf("\033[37;");
		break;

	case back::yellow:
		printf("\033[33;");
		break;
	}
}


// ���ù�ͬ����
void ConsoleOutAttribute(mode attr)
{
	switch(attr)
	{
	case mode::back_bold:
		printf("");
		break;

	case mode::fore_bold:
		printf("");
		break;

	case mode::underline:
		printf("\33[4m");
		break;
	}
}


// ��ԭ��Ĭ������
void ConsoleOutAttributeRest()
{
	printf("\33[0m");
}

#endif // OS_LINUX


