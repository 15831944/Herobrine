// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
		: Command("help", "��ʾ���������Ϣ", "Herobrine")
	{
	}

	void excute(Console& console) override
	{
	}
};


