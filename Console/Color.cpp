// Copyright 2019 SMS
// License(Apache-2.0)
// �޸Ŀ���̨��������

#include "Color.h"

typedef unsigned int uint;

std::map<unsigned int, Color::pair> Color::pairs;



// �����ɫ����
void Color::add(uint id, Fore fore, Back back, Mode mode)
{
	pairs.insert(std::pair<uint, pair>(id, {fore, back, mode}));
}

// ʹ����ɫ����
void Color::set(uint id)
{
	set(pairs[id].fore);
	set(pairs[id].back);
	set(pairs[id].mode);
}


#ifdef OS_WIN

HANDLE Color::hStdOut;
WORD	 Color::attr;
WORD	 Color::defAttr;


// ����ǰ��ɫ
void Color::set(Fore attr)
{
	Color::attr &= 0xf0;
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}

// ���ñ���ɫ
void Color::set(Back attr)
{
	Color::attr &= 0x0f;
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}

// ������������
void Color::set(Mode attr)
{
	Color::attr |= (WORD)attr;
	SetConsoleTextAttribute(hStdOut, Color::attr);
}


// ��ԭĬ������
void Color::reset()
{
	attr = defAttr;
	SetConsoleTextAttribute(hStdOut, attr);
}


class WinColorInit
{
public:
	WinColorInit()
	{
		Color::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// ��ȡ��ǰ�������ַ�����
		CONSOLE_SCREEN_BUFFER_INFO bufInfo;
		GetConsoleScreenBufferInfo(Color::hStdOut, &bufInfo);
		Color::defAttr = bufInfo.wAttributes;
		Color::attr		 = bufInfo.wAttributes;
	}
};

WinColorInit winColorInit;

#endif // OS_WIN
