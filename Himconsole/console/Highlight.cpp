// Copyright 2019 SMS
// License(Apache-2.0)
// ����

#include "Highlight.h"
#include "Console.h"



Highlight::Highlight()
		: console(nullptr)
{
	color.command.fore = Attribute::fore::green;
	color.command.mode = Attribute::mode::fore_bold;
	color.key.fore		 = Attribute::fore::yellow;
	color.key.mode		 = Attribute::mode::fore_bold;
	color.delim.fore	 = Attribute::fore::white;
	color.delim.mode	 = Attribute::mode::fore_bold;
}

Highlight::Highlight(Console* console)
		: console(console)
{
	color.command.fore = Attribute::fore::green;
	color.command.mode = Attribute::mode::fore_bold;
	color.key.fore		 = Attribute::fore::yellow;
	color.key.mode		 = Attribute::mode::fore_bold;
	color.delim.fore	 = Attribute::fore::white;
	color.delim.mode	 = Attribute::mode::fore_bold;
}


// �����ؼ���
void Highlight::run()
{
	switch(console->state)
	{
	case Console::State::COMMAND:
		if(console->pCommand == nullptr)
			break;
		Attribute::set(color.command.fore);
		Attribute::set(color.command.mode);
		break;

	case Console::State::KEY:
		if(console->pKey == nullptr)
			break;
		Attribute::set(color.key.fore);
		Attribute::set(color.key.mode);
		break;

	case Console::State::DELIM:
		Attribute::set(color.delim.fore);
		Attribute::set(color.delim.mode);
		printf(":");
		Attribute::rest();
		return;
	}
	for(size_t i = 0; i < console->buf.size(); i++)
		printf("\b \b");
	printf("%s", console->buf.c_str());
	Attribute::rest();
}


void Highlight::setCommandFore(Attribute::fore attr)
{
	color.command.fore = attr;
}

void Highlight::setCommandMode(Attribute::mode attr)
{
	color.command.mode = attr;
}

void Highlight::setKeyFore(Attribute::fore attr)
{
	color.key.fore = attr;
}

void Highlight::setKeyMode(Attribute::mode attr)
{
	color.key.mode = attr;
}

void Highlight::setDelimFore(Attribute::fore attr)
{
	color.delim.fore = attr;
}

void Highlight::setDelimMode(Attribute::mode attr)
{
	color.delim.mode = attr;
}
