#pragma once
#include<string>
#include <vector>
#include <map>
#include <mutex>
#include "typedefine.h"
#include<random>  
#include<time.h>  
#include "TinyChan.h"
using namespace std;
class TimeController
{
public:
	static LONGLONG StringToDateSum(string str);
	static LONGLONG ToDateSum(LONGLONG year, LONGLONG month, LONGLONG day, LONGLONG hour, LONGLONG min, LONGLONG sec);
	TimeController();
	~TimeController();
	void SetTime();
	bool IsSameDay();
	bool IsSameHour();
	bool IsSameMin();
	bool IsSameSec();
	static LONGLONG GetNowDateSum();

	static string Get_Year_Day_String();
	static string Get_Year_Day_Hour_String();
	static string Get_Year_Day_Hour_Min_String();
	static int Get_Year_Day_Hour_Min_Mult();
	static string Get_Year_Day_Hour_Min_Sec_String();
private:

	int Presec;
	int Premin;
	int Prehour;
	int Preday;
};

