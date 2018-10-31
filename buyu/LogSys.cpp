#include "StdAfx.h"
#include "LogSys.h"
#include "TimeController.h"

LogSys::LogSys()
{
	openingConsole = false;
}


LogSys::~LogSys()
{
}

void LogSys::Init(string path) {
	FilePath = path;
}
void LogSys::LogMessage(string msg) {

	LogInWindow(msg);
	LogInFile(msg);
}
void LogSys::LogInWindow(string msg, enTraceLevel level ) {

	CString sz;
	sz = msg.c_str();
	CTraceService::TraceString(sz, level);

}
void LogSys::LogInFile(string msg) {

	string m = TimeController::Get_Year_Day_Hour_Min_Sec_String() + msg;

	ofout.open(FilePath+ TimeController::Get_Year_Day_String()+"��־���.json", ios::in | ios::app);

	if (ofout.is_open())
	{
		ofout << m;

		ofout.close();
	}
}
void LogSys::CreateConsole() {

	if (!openingConsole) {
		AllocConsole();
		//HANDLE��hOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);//��ÿ���̨������
		SetConsoleTitleA("");
		freopen("CONOUT$", "w", stdout);
		//freopen("CONIN$", "r", stdin);
		//std::cout << "�ر����ӽ��ȣ�" << std::endl;
		openingConsole = true;
	}
	

	//std::thread ProductLogicThreadHandle(&ConsoleControl::ConsoleThread, this);
	//ProductLogicThreadHandle.detach();
}
void LogSys::DeleteConsole() {

	FreeConsole();
}
void LogSys::LogInConsole(string msg) {
	CreateConsole();
	std::cout << msg << std::endl;
}