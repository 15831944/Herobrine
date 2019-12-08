// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class Clear : public Command
{
public:
	Clear()
		: Command("clear", "��������л�����", "Herobrine")
	{
	}

	void excute()
	{
		#ifdef OS_WIN
			system("cls");
		#elif OS_LINUX
			system("clear");
		#endif
	}

};


