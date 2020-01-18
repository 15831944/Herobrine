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
			printf("����:\n  %s\n\n", cmd->getDescription().c_str());
			printf("����:\n  %s\n\n", cmd->getAuthor().c_str());
			printf("��ԴЭ��:\n  ");
			switch(cmd->getLicense())
			{
			case License::Apache_2_0:
				puts("Apache 2.0 http://www.apache.org/licenses/LICENSE-2.0");
				break;

			case License::TIM:
				puts("TIM http://www.opensource.org/licenses/mit-license.php");
				break;

			case License::GPL_3_0:
				puts("GPL 3.0 https://www.gnu.org/licenses/gpl-3.0.en.html");
				break;

			case License::LGPL_3_0:
				puts("LGPL 3.0 https://opensource.org/licenses/LGPL-3.0");
				break;

			case License::BSD_2_Clause:
				puts("BSD 2-Clause https://opensource.org/licenses/BSD-2-Clause");
				break;

			case License::BSD_3_Clause:
				puts("BSD 3-Clause https://opensource.org/licenses/BSD-3-Clause");
				break;

			case License::MPL_2_0:
				puts("MPL 2.0 https://opensource.org/licenses/MPL-2.0");
				break;
			}
		}
	}
};
