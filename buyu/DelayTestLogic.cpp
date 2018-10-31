#include "Global.h"
#include "GameTable.h"

#include "LogSys.h"
#include "MessageHelper.h"
void GameTable::TestDelayUpdate(int frame) {

	for (int i = 0; i < GAME_PLAYER; i++) {

		int frameOffset = 0;
		if (ClientFrame[i].TryGetFrameOffset(frameOffset)) {
			/*char ch[50];
			sprintf_s(ch, "frameOffset %d", frameOffset);
			g_global.logSys->LogInWindow(ch);*/
			StartGame(i, frameOffset);
		}
	}
}
void GameTable::Revieve_DelayTest(WORD chairId, R_TestDelay* pack) {
	ClientFrame[chairId].RevieveDalayTest();
	g_global.messageHelper->Back_R_TestDelay(pack);
}