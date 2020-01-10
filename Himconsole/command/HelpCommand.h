// Copyright 2019 SMS
// License(Apache-2.0)

#include "../command.h"



class HelpCommand : public Command
{
public:
	HelpCommand()
			: Command("��ʾ���������Ϣ", "Herobrine")
	{
		syntax.insert({"command", Syntax(Syntax::Type::STRING, "Ҫ��ʾ������Ϣ������", true)});
	}

	void excute(Console& console) override
	{
		if(console.getArgSize() == 0)
		{
			auto& cmds = console.getCommand();
			for(auto& cmd : cmds)
				printf("%-15s %s\n", cmd.first.c_str(), cmd.second->getDescription().c_str());
		}
		else
		{
			auto name = console.getStringArg("command");
			auto cmd	= console.getCommand(name);
			if(cmd == nullptr)
				throw "δ�ҵ�����";
			printf("����:\n\t%s\n\n", cmd->getDescription().c_str());
			printf("����:\n\t%s\n\n", cmd->getAuthor().c_str());
			printf("��ԴЭ��:\n\t");
			switch(cmd->getLicense())
			{
			case License::Apache_2_0:
				printf("Apache 2.0");
				break;

			case License::TIM:
				printf("TIM");
				break;
			}
		}
	}
};
