#pragma once
#include "Global.h"
class ItemModel;
class MessageModel;
class ScoreModel
{
public:
	ScoreModel();
	~ScoreModel();

	void Bind(ItemModel* host, MessageModel* message);
	void Init(LONGLONG value);
	void AddScore(LONGLONG score, bool isBankOpreate = false);
	bool TrySubScore(LONGLONG score);
	LONGLONG GetScore();
	LONGLONG GetWinLoseScore();
	void ResetWinLoseScore();
	
private:

	LONGLONG Value;
	LONGLONG WinLoseScore;
	ItemModel* Host;
	MessageModel* Message;
};
