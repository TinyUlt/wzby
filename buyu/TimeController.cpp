#include "TimeController.h"
#include <time.h>

TimeController::TimeController()
{
}


TimeController::~TimeController()
{
}
void TimeController::SetTime() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	Presec = t->tm_sec;
	Premin = t->tm_min;
	Prehour = t->tm_hour;
	Preday = t->tm_mday;
}
bool TimeController::IsSameDay() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	return t->tm_mday == this->Preday;
}
bool TimeController::IsSameHour() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	return t->tm_hour == this->Prehour;
}
bool TimeController::IsSameMin() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	return t->tm_min == this->Premin;
}
bool TimeController::IsSameSec() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	return t->tm_sec == this->Presec;
}

string TimeController::Get_Year_Day_String() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	char ch[100];
	sprintf(ch, "[%d年%02d月%02d日]",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday);

	return ch;
}
string TimeController::Get_Year_Day_Hour_String() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	char ch[100];
	sprintf(ch, "[%d年%02d月%02d日%02d时]",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour);

	return ch;
}
string TimeController::Get_Year_Day_Hour_Min_String() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	char ch[100];
	sprintf(ch, "[%d年%02d月%02d日%02d时%02d分]",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min);

	return ch;
}
string TimeController::Get_Year_Day_Hour_Min_Sec_String() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	char ch[100];
	sprintf(ch, "[%d年%02d月%02d日%02d时%02d分%02d秒]",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec);

	return ch;
}
int TimeController::Get_Year_Day_Hour_Min_Mult() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	return t->tm_year * t->tm_mon * t->tm_mday * t->tm_hour * t->tm_min * t->tm_sec;
}
LONGLONG TimeController::GetNowDateSum() {
	time_t tt = time(NULL);
	tm* t = localtime(&tt);
	//return ToDateSum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	return ToDateSum(t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作  
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

LONGLONG TimeController::StringToDateSum(string str) {

	LONGLONG sum = 0;

	std::vector<std::string> result = split(str, ".");

	if (result.size() == 6) {

		sum = ToDateSum(atoi(result[0].c_str()) - 1900, atoi(result[1].c_str()) - 1, atoi(result[2].c_str()), atoi(result[3].c_str()), atoi(result[4].c_str()), atoi(result[5].c_str()));
	}
	else {
	}


	
	return sum;

}
LONGLONG TimeController::ToDateSum(LONGLONG year, LONGLONG month, LONGLONG day, LONGLONG hour, LONGLONG min, LONGLONG sec) {

	struct tm info;
	//char buffer[80];

	info.tm_year = year;
	info.tm_mon = month;
	info.tm_mday = day;
	info.tm_hour = hour;
	info.tm_min = min;
	info.tm_sec = sec;
	info.tm_isdst = -1;
	
	return mktime(&info);
	//return sec + min * 60 + hour * 60 * 60 + day * 24 * 60 * 60 + month * 30 * 24 * 60 * 60 + year * 12 * 30 * 24 * 60 * 60;
}