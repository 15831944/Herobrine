// Copyright 2019 SMS
// License(Apache-2.0)
// ������

#include "console.h"
#include "localization.h"
#include <ctype.h>

#ifdef OS_WIN
#include <conio.h>
#endif



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
	return args.at(key);
}

int Console::getIntArg(const string& key)
{
	return stoi(args.at(key));
}

long Console::getLongArg(const string& key)
{
	return stol(args.at(key));
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


void Console::addCommand(const string& name, Command* cmd)
{
	if(getCommand(name) != nullptr)
		; // TODO

	commands.insert({name, cmd});
}


Command* Console::getCommand(const string& name)
{
	auto res = commands.find(name);
	if(res == commands.end())
		return nullptr;
	return res->second;
}


const map<string, Command*>& Console::getCommand()
{
	return commands;
}



enum class InputState
{
	CMD, // ��������
	KEY, // �����
	ARG	 // ����ֵ
};

void Console::run()
{
	InputState inputState = InputState::CMD;

	while(true)
	{
		string buf;

		PrintPrompt();

		while(true)
		{
			char ch = GetChar();

			switch(inputState)
			{
			case InputState::CMD:
				break;

			case InputState::KEY:
				break;

			case InputState::ARG:
				break;
			}

			buf += ch;
		}

		buf.clear();
	}
}



void Console::console()
{
	string key, value;

	while(true)
	{
		Syntax*	 syntax = nullptr;
		Command* cmd		= nullptr;
		string*	 arg		= nullptr;

		size_t				 cPos = 0; // ��ǰ���λ��
		vector<size_t> lPos;		 // ����/������β

		size_t keySize = 0;

		bool inputValue	 = false; // ��������ֵ
		bool inputString = false; // ���������ַ���

		PrintPrompt();

		// ���� ����
		// TODO(SMS): �˴��Ƿ�Ҫʹ��goto��������
		while(true)
		{
			string buf;

			char ch = GetChar();

			if(!isprint(ch))
			{
				printf("\a");
				continue;
			}

			if(ch == ' ' || ch == '\r')
			{
				cmd = getCommand(buf);
				if(cmd == nullptr)
				{
					printf("\a");
					continue;
				}
				break;
			}

			buf += ch;
		}

		while(true)
		{
			char ch = GetChar();

			if(inputValue)
			{
				// ���� ֵ
				if(arg == nullptr)
					arg = &args[key];

				if(ch == '\r' || (inputString == false && ch == ' '))
				{
					inputValue = false;
					key.clear();
					break;
				}

				switch(cmd->syntax[key].type)
				{
				case Syntax::Type::INT:
			case Syntax::Type::LONG:
				if(!isalnum(ch))
				{
					printf("\a");
					continue;
				}
				break;

			case Syntax::Type::FLOAT:
			case Syntax::Type::DOUBLE:
				if(!isalnum(ch) && ch != '.')
				{
					printf("\a");
					continue;
				}
				break;

			case Syntax::Type::STRING:
				if(!isprint(ch))
				{
					printf("\a");
					continue;
				}
				if(ch == '"')
					if(!inputString)
						inputString = true;
					else
						inputString = false;
				break;

			case Syntax::Type::OPTION:
				if(!isalnum(ch) && ch != '_')
				{
					printf("\a");
					continue;
				}
				break;
			}

			if(ch == '"')
				break;

			arg += ch;
		}
		else
		{
			// ���� ��
		}

		if(ch == '\r')
		{
			printf("\n");
			break;
		}

		printf("%c", ch);
		cPos++;
	}

	args.clear();

	assert(cmd != nullptr);

	try
	{
		cmd->excute(*this);
	}
	catch(char* error)
	{
		print::error(error);
	}
}
}


/*

				if(!isalnum(ch) && ch != ' ' && ch != '_' && ch != '\r' && ch != '\b')
				{
					printf("\a");
					continue;
				}

				if(cmd == nullptr || ch == ' ' || ch == '\r')
				{
					cmd = getCommand(key);
					if(cmd == nullptr)
					{
						if(key == "exit")
							return;

						printf("\a");
						continue;
					}
				}

				switch(ch)
				{
				case ' ':
					// �Ƿ��������������ո�
					if(key.size() == 0)
					{
						printf("\a");
						continue;
					}

					// �Ƿ���Լ�����д����
					if(cmd->syntax.size() <= args.size())
					{
						printf("\a");
						continue;
					}

					lPos.push_back(cPos);
					inputValue = true;
					arg = nullptr;
					break;

				case '\r':
					// �Ƿ���Բ���д�κβ���(�������ȫ����д���)
					if(cmd->syntax.size() != 0)
						for(auto& s : cmd->syntax)
							if(s.second.required == false)
							{
								printf("\a");
								continue;
							}
					
					lPos.push_back(cPos);
					inputValue = true;
					break;

				case '\b':
					if(cPos > 0)
					{
						cPos--;
						printf("\b \b");

						// �ص���һ������
						if(cPos == lPos.back())
						{
							cPos = lPos.back();
							key  = 
							lPos.pop_back();
							inputValue = true;
							arg = nullptr;
							continue;
						}

						key.pop_back();
					} else
					{
						printf("\a");
						continue;
					}

				default:
					key += ch;
				}
*/


// �����������ʾ��
void Console::PrintPrompt()
{
	printf("\n");
	Attribute::set(Attribute::mode::underline);
	printf(prompt.c_str());
	Attribute::rest();
	printf("> ");
}


// ����һ���ַ�, ������
inline int Console::GetChar()
{
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
