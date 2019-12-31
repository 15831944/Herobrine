// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#include "console.h"
#include "localization.h"




Console::Console()
{
	history.resize(historySize);
}


Console::~Console()
{
}


size_t Console::getArgSize()
{
	return args.size();
}


const string& Console::getStringArg(const string& key)
{
	return args.at(key).value;
}

int Console::getIntArg(const string& key)
{
	return stoi(args.at(key).value);
}

long Console::getLongArg(const string& key)
{
	return stol(args.at(key).value);
}


void Console::setPrompt(const string& prompt)
{
	this->prompt = prompt;
}


void Console::setHistorySize(size_t size)
{
	historySize = size;
	history.resize(historySize);
}

const string& Console::getHistory(size_t id)
{
	return history.at(id);
}

size_t Console::getHistorySize()
{
	return history.size();
}


void Console::addCommand(Command* cmd)
{
	command.push_back(cmd);
	command.shrink_to_fit();
}


Command* Console::getCommand(const string& name)
{
	for(size_t i = 0; i < command.size(); i++)
		if(command[i]->getName() == name)
			return command[i];
	return nullptr;
}

Command* Console::getCommand(size_t id)
{
	return command.at(id);
}


size_t Console::getCommandSize()
{
	return command.size();
}



void Console::console()
{
	while(true)
	{
		PrintPrompt();
		string buf = ReadLine();

		if (buf.size() == 0)
			continue;

		// ȥ������ո�
		size_t pos;
		while ((pos = buf.find("  ")) != string::npos)
			buf.replace(pos, 2, " ");

		// ���������ʷ��¼
		if (history.size() == historySize)
			history.pop_back();
		history.push_front(buf);
		history.begin()->shrink_to_fit();

		// �ָ��������
		size_t lastPos;
		lastPos = buf.find(' ');
		string commandName = buf.substr(0, lastPos);
		

		// �˳�������
		if (commandName == "exit")
			return;

		// ִ������
		auto cmd = commands[commandName];
		try
		{
			cmd->excute(*this);
		}
		catch(char* error)
		{
			print::error(error);
		}

			CheckSyntax(cmd);

		// print::error(local::ERROR_UNKNOWN_COMMAND);
	}
}


string Console::ReadLine()
{
	string cmd;

	size_t pPredict = -1;    // ����Ԥ��ָ��
	size_t pHistory = -1;    // ������ʷָ��

	while (true)
	{
		char buf = Input();

		// �߽���
		if (cmd.size() >= cmd.max_size())
		{
			print::error(local::ERROR_COMMAND_TOO_LONG);
			cmd.clear();
			break;
		}

		// ���ܼ�
		if (buf == -32 || buf == 0)
		{
			buf = Input();

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
			
			Attribute::set(Attribute::fore::white);
			Attribute::set(Attribute::mode::fore_bold);
			
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
			Attribute::set(Attribute::fore::white);
			Attribute::set(Attribute::mode::fore_bold);

			printf("%c", buf);
			cmd += buf;
		}
	}

	Attribute::rest();
	
	return cmd;
}


// �����������ʾ��
void Console::PrintPrompt()
{
		printf("\n");
		Attribute::set(Attribute::mode::underline);
		printf(prompt.c_str());
		Attribute::rest();
		printf("> ");
}


void Console::SplitCmdToArg(const string& cmd)
{
}


// ����ǲ����Ƿ�Ϸ�
bool Console::CheckSyntax(Command* cmd)
{
	// TODO: ����Ҫ�������Ƿ�Ϸ�, ֻ��Ҫ��ReadLine�����û��޷��������Ĳ�������

	return false;
}


// ����һ���ַ�, ������
inline int Console::Input() {
#ifdef OS_WIN
	return _getch();
#endif

#ifdef OS_LINUX
	system("stty -echo");
	system("stty -icanon");
	char c = getchar();
	system("stty icanon");
	system("stty echo");
	return c;
#endif
}


