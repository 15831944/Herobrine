// Copyright 2019 SMS
// License(Apache-2.0)
// �޸Ŀ���̨��������
// ƽ̨: Windows

#include "attribute.h"



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


