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
	historys.resize(historySize);
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
	historys.resize(historySize);
}

const deque<string>& Console::getHistory()
{
	return historys;
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



// ����״̬, ��ǰ������Ĳ���
enum class State
{
	COMMAND, // ��������
	KEY,		 // �����
	VALUE		 // ����ֵ
};


// ������Ϣ
struct Highlight
{
	struct Tuple
	{
		bool						isLight;
		Attribute::fore fore;
		// Attribute::back back;
		Attribute::mode mode;
	};

	Tuple command;
	Tuple key;
	Tuple value;
	Tuple string;
	Tuple number;
	Tuple delim;
};


void Console::run()
{
	while(true)
	{
		string	 buf;
		Command* command = nullptr;

		PrintPrompt();

		while(true)
		{
			State					state = State::COMMAND;
			size_t				pos		= 0;
			const string* match = nullptr;

			Highlight highlight;
			highlight.command.fore = Attribute::fore::yellow;
			highlight.command.mode = Attribute::mode::fore_bold;
			highlight.key.fore		 = Attribute::fore::blue;
			highlight.key.mode		 = Attribute::mode::fore_bold;

			char ch = GetChar();


			if(ch == '\r')
			{
				printf("\n");
				break;
			}


			// ���������ַ�
			switch(ch)
			{
			case ' ':
				switch(state)
				{
				case State::COMMAND:
					if(command == nullptr)
						continue;
					state = State::VALUE;
					buf.clear();
					break;

				case State::VALUE:
					state = State::KEY;
					buf.clear();
					break;

				case State::KEY:
					continue;
				}
				break;

			case ':':
				break;

			case '\b':
				switch(state)
				{
				case State::COMMAND:
					if(buf.empty())
						continue;
					printf("\b \b");
					buf.pop_back();
					break;

				case State::KEY:
					// ��ԭbuf
					break;
				}

			case '\t':
				if(match == nullptr)
					continue;
				printf("%s", match->substr(buf.size(), pos - buf.size()).c_str());
				buf += match->substr(buf.size(), pos - buf.size());
				break;
			}


			// ����Ϸ��Լ��
			switch(state)
			{
			case State::COMMAND:
			case State::KEY:
				if(!isalnum(ch))
					continue;
				break;

			case State::VALUE:
				break;
			}


			printf("%c", ch);
			buf += ch;


			// ����
			switch(state)
			{
			case State::COMMAND:
				command = getCommand(buf);
				if(command != nullptr)
				{
					Attribute::set(highlight.command.fore);
					Attribute::set(highlight.command.mode);
				}
				for(size_t i = 0; i < buf.size(); i++)
					printf("\b \b");
				printf("%s", buf.c_str());
				Attribute::rest();
				break;
			}


			vector<const string*> matchs;
			switch(state)
			{
			case State::COMMAND:
				for(auto& cmd : commands)
					if(buf == cmd.first.substr(0, buf.size()))
						matchs.push_back(&cmd.first);

				if(matchs.size() == 0)
				{
					match = nullptr;
					break;
				}

				match = matchs.back();
				matchs.pop_back();

				if(matchs.size() > 1)
				{
					pos			 = 0;
					size_t i = commands.size();
					while(true)
					{
						for(auto cmd : matchs)
						{
							if(cmd->size() <= i)
								pos = i;
							else if(match[i] != cmd[i])
								pos = i;
							break;
						}
						if(pos)
							break;
						i++;
					}
				}
				else
					pos = match->size() - 1;
				break;

			case State::KEY:
				break;
			}
			matchs.clear();
		}

		buf.clear();

		assert(command != nullptr);

		try
		{
			command->excute(*this);
		}
		catch(const char* error)
		{
			print::error(error);

			// ж�س��������
		}
	}
}



/*
void Console::run()
{
	InputState		 inputState = InputState::CMD;
	Syntax*				 syntax			= nullptr;
	vector<string> stack;

	while(true)
	{
		string	cmd, arg;
		string* buf = &cmd;

		PrintPrompt();

		while(true)
		{
			char ch = GetChar();

			switch(ch)
			{
			case '\r':
				break;

			case ':':
				break;

			case ' ':
				break;

			case '\b':
				if(buf->size() > 0)
				{
					printf("\b \b");
					buf->pop_back();
				}
				else if(inputState == InputState::CMD)
				{
					printf("\a");
					continue;
				}
				else
				{
					if(stack.size() > 0)
					{
						if(inputState == InputState::KEY)
						{
							inputState = InputState::ARG;
							buf				 = &args[stack.back()];
						}
						if(inputState == InputState::ARG)
						{
							inputState = InputState::CMD;
							buf				 = &arg;
							stack.pop_back();
						}
					}
					else
					{
						printf("\a");
						continue;
					}
				}
				break;
			}

			switch(inputState)
			{
			case InputState::CMD:
				if(!isalnum(ch))
				{
					printf("\a");
					continue;
				}
				break;

			case InputState::KEY:
				if(!isalnum(ch))
				{
					printf("\a");
					continue;
				}
				break;

			case InputState::ARG:
				break;
			}

			printf("%c", ch);
			buf += ch; // *buf
		}
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
*/

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
