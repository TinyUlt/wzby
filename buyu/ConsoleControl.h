#pragma once
#include <string>
using namespace std;
class ConsoleControl
{
public:
	ConsoleControl();
	~ConsoleControl();
	void Init(string roomName);
	void ConsoleThread();
};

