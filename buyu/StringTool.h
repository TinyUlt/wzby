#pragma once
#include "StdAfx.h"
#include "typedefine.h"
#include <string>
#include <vector>
using namespace std;
class StringTool {
public:
	//编码转换
	static wchar_t *Utf_8ToUnicode(char* szU8) {
		//UTF8 to Unicode
		//由于中文直接复制过来会成乱码，编译器有时会报错，故采用16进制形式

		//预转换，得到所需空间的大小
		int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
		//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
		wchar_t* wszString = new wchar_t[wcsLen + 1];
		//转换
		::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
		//最后加上'\0'
		wszString[wcsLen] = '\0';
		return wszString;
	};
	static void Wchar_tToString(std::string& szDst, wchar_t *wchar) {
		wchar_t * wText = wchar;
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
		char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
		psText = new char[dwNum + 1];
		WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
		szDst = psText;// std::string赋值
		delete[]psText;// psText的清除
	};
	static void ToChinese(string & str, char outch[MAX_PATH]) {

		//解决中文转码问题  
		int len = strlen(str.c_str()) + 1;
		//char outch[MAX_PATH];
		WCHAR * wChar = new WCHAR[len + 1];
		wChar[0] = 0;
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, wChar, len);
		WideCharToMultiByte(CP_ACP, 0, wChar, len, outch, len, 0, 0);
		delete[] wChar;
	};
	static string GBKToUTF8(const std::string& strGBK) {
		string strOutUTF8 = "";
		WCHAR * str1;
		int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
		str1 = new WCHAR[n + 1];
		MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
		n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
		char * str2 = new char[n + 1];
		WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
		strOutUTF8 = str2;
		delete[]str1;
		str1 = NULL;
		delete[]str2;
		str2 = NULL;
		return strOutUTF8;
	};
	static string TCHAR2STRING(TCHAR *STR) {

		int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);

		char* chRtn = new char[(iLen + 1) * sizeof(char)];

		WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

		std::string str(chRtn);
		delete[] chRtn;
		chRtn = NULL;
		return str;
	};
	static string LPCTSTR2STRING(LPCTSTR STR) {
		char ch[64];
		WideCharToMultiByte(CP_ACP, 0, STR, -1, ch, LEN_MD5, 0, 0);

		return ch;
	};
	static std::vector<std::string> split(std::string str, std::string pattern) {
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
	};
};