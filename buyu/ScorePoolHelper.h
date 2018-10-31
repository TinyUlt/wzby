#pragma once
#include "typedefine.h"
using namespace std;
class ScorePoolHelper
{
public:
	ScorePoolHelper();
	~ScorePoolHelper();
	bool TryGetScore(int multiple, LONGLONG& score);
};

