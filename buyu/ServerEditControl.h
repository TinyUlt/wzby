#pragma once
#include<string>
using namespace std;
class ServerEditControl
{
public:
	ServerEditControl();
	~ServerEditControl();

	string GetRedpackJsonData();
	bool SetRedpackJsonData(string data);

	string GetFishStoreJsonData(string path);
	
	string GetJsonData(string path);
	string GetRedpackCostJsonData(string path);
};

