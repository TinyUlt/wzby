#include "ConsoleControl.h"
#include <Windows.h>

#include <io.h>

#include <stdio.h>

#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <thread>

ConsoleControl::ConsoleControl()
{
}


ConsoleControl::~ConsoleControl()
{
}
void ConsoleControl::Init(string roomName) {

	

	/*AllocConsole();
	SetConsoleTitleA(roomName.c_str());
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	std::cout << "This is a test info" << std::endl;

	std::thread ProductLogicThreadHandle(&ConsoleControl::ConsoleThread, this);
	ProductLogicThreadHandle.detach();*/
}
void ConsoleControl::ConsoleThread() {

	int input=-1;
	while (cin >> input)
	{
	
		if (input == 1) {
			int a = 1;
			a++;
		}
	}
}