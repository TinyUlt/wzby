#pragma once
#pragma pack(1)

//#include <string>
//#include <vector>
using namespace std;
struct CMD_GP_C_PropertyBuy
{
	BYTE cbConsumeMode;                     //消费模式   1银行   2身上
	WORD wItemCount;                            //购买数目
	WORD wPropertyIndex;                        //道具索引	
	DWORD dwTargetUserID;						//对象
};
struct CMD_GP_PropertyFailure
{
	TCHAR szDescribeString[128];//[128];				//描述消息
};

class CMD_GP_PropertySuccess
{
	LONGLONG lUserScore;
	BYTE cbMemberOrder;
	TCHAR szMemberDay[128];//[128];				//描述消息
};
