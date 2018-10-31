#include "Global.h"
#include "ScorePoolHelper.h"



ScorePoolHelper::ScorePoolHelper()
{
}


ScorePoolHelper::~ScorePoolHelper()
{
}

bool ScorePoolHelper::TryGetScore(int multiple, LONGLONG& score) {

	if (rand() % multiple == 0) {

		score = multiple;
		return true;
	}

	return false;
}