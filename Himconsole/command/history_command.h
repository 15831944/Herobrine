// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HistoryCommand : public Command
{
public:
	HistoryCommand()
		: Command("history", "��ʾ������ʷ��¼", "Herobrine")
	{
	}

	void excute(Console& console) override
	{
	}
};


