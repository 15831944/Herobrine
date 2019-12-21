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

	void excute(Console& console) override
	{
#ifdef OS_WIN
			system("cls");
#endif

#ifdef OS_LINUX
			printf("\33[2J");
#endif
	}

};


