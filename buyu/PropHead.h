#pragma once
#pragma pack(1)

//#include <string>
//#include <vector>
using namespace std;
struct CMD_GP_C_PropertyBuy
{
	BYTE cbConsumeMode;                     //����ģʽ   1����   2����
	WORD wItemCount;                            //������Ŀ
	WORD wPropertyIndex;                        //��������	
	DWORD dwTargetUserID;						//����
};
struct CMD_GP_PropertyFailure
{
	TCHAR szDescribeString[128];//[128];				//������Ϣ
};

class CMD_GP_PropertySuccess
{
	LONGLONG lUserScore;
	BYTE cbMemberOrder;
	TCHAR szMemberDay[128];//[128];				//������Ϣ
};
