// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#include "console.h"
#include "localization.h"



Console::Console()
{
}


Console::~Console()
{
}


// ��ȡ��������
size_t Console::getArgSize()
{
	return arg.size();
}


// ��ȡ����
const string& Console::getArg(const string& key)
{
	return arg[key];
}


void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}

void Console::setHistorySize(size_t size)
{
	historySize = size;
}


void Console::addCommand(Command* cmd)
{
	command.push_back(cmd);
}


void Console::console()
{
	string cmd;
	size_t pos;

	while(true)
	{
		PrintPrompt();
		cmd = ReadLine();

		if (cmd.size() == 0)
			continue;

		// ȥ������ո�
		while ((pos = cmd.find("  ")) != string::npos)
			cmd.replace(pos, 2, " ");

		// ���������ʷ��¼
		if (history.size() == historySize)
			history.pop_back();
		history.push_front(cmd);
		history.begin()->shrink_to_fit();

		// �ָ��������
		size_t lastPos;
		lastPos = cmd.find(' ');
		arg["cmd"] = cmd.substr(0, lastPos);
		

		// �˳�������
		if (arg["cmd"] == "exit")
			return;

		// ���Ҳ�ִ������
		for(auto& c : command)
			if(c->getName() == arg["cmd"])
			{
				print::good("");
				c->excute();
				continue;
			}

		print::error(LOC_ERROR_UNKNOWN_COMMAND);
	}
}


string Console::ReadLine()
{
	string cmd;

	size_t pPredict = -1;    // ����Ԥ��ָ��
	size_t pHistory = -1;    // ������ʷָ��

	while (true)
	{
		char buf = _getch();	// TODO(SMS): ���ڿ���ֲ������

		// �߽���
		if (cmd.size() >= cmd.max_size())
		{
			print::error(LOC_ERROR_COMMAND_TOO_LONG);
			cmd.clear();
			break;
		}

		// ���ܼ�
		if (buf == -32 || buf == 0)
		{
			buf = _getch();	   // ��ȡ���ܼ�ASCII���� // TODO(SMS): ���ڿ���ֲ������

			if (history.empty())
				continue;

			// ��/�¼� �л�������ʷ��¼
			if (buf == 72)  	 // �ϼ�
			{
				if (pHistory == -1)
					pHistory = 0;
				else if (pHistory < history.size() - 1)
					pHistory++;
				else
					continue;
			}

			if (buf == 80)	   // �¼�
			{
				if (pHistory == -1)
					pHistory = 0;
				else if (pHistory > 0)
					pHistory--;
				else
					continue;
			}

			// �л���ָ����������ʷ��¼
			if (buf == 72 || buf == 80)
			{
				for (size_t i = 0; i < cmd.size(); i++)
					printf("\b \b");
				cmd = history[pHistory];
				printf(cmd.c_str());
			}

			continue;
		}

		// Enter�� ��������
		if (buf == '\r')
		{
			printf("\n");
			break;
		}

		// Tab�� ��ȫ����
		if (buf == '\t')
		{
			if (pPredict == -1)	// û��ƥ����
				continue;
			
			ConsoleOutAttribute(fore::white);
			ConsoleOutAttribute(mode::fore_bold);
			
			printf("%s", &(command[pPredict]->getName()[cmd.size()]));
			cmd += &(command[pPredict]->getName()[cmd.size()]);

			continue;
		}
		
		// ESC�� �������
		if (buf == 27)
		{
			for (size_t i = 0; i < cmd.size(); i++)
				printf("\b \b");

			pPredict = -1;
			pHistory = -1;
			cmd.clear();

			continue;
		}

		// ���˷Ƿ��ַ�
		if (false)
			; // TODO(SMS): �д�����, ע�����ɶ���

		if (buf == '\b')
		{
			// Backspace�� ɾ����һ���ַ�
			if (cmd.size() <= 0)
				continue;
			printf("\b \b");
			cmd.pop_back();
		}
		else
		{
			// ����������ַ�
			ConsoleOutAttribute(fore::white);
			ConsoleOutAttribute(mode::fore_bold);

			printf("%c", buf);
			cmd += buf;
		}

	}

	ConsoleOutAttributeRest();
	
	return cmd;
}


// �����������ʾ��
void Console::PrintPrompt()
{
		printf("\n");
		ConsoleOutAttribute(mode::underline);
		printf(prompt.c_str());
		ConsoleOutAttributeRest();
		printf("> ");
}


void Console::SplitCmdToArg(const string& cmd)
{
}


// ����ǲ����Ƿ�Ϸ�
bool Console::CheckSyntax()
{
	return false;
}


