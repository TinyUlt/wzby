#pragma once
#include<string>
#include<iostream>
#include <fstream>
#include<sstream>

using namespace std;
class LogSys
{
public:
	LogSys();
	~LogSys();

	string FilePath;
	void Init(string path);
	void LogMessage(string msg);
	void LogInWindow(string msg, enTraceLevel level = TraceLevel_Info);
	void LogInFile(string msg);
	void LogInConsole(string msg);

	void CreateConsole();
	void DeleteConsole();
	//Âß¼­Ëø
	bool openingConsole;
	
	ofstream ofout;
};

