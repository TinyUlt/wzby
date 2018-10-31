#include "Global.h"
#include "GameTable.h"

void GameTable::TestUpdate(int frame) {
	S_FrameSync frameSync;
	frameSync.set_frame(frame);
	ItemManager.TryGetMonstersPoint(frameSync.mutable_monsters());
	//PlayerManager.TryGetMonstersPoint(frameSync.mutable_players());
	BulletManager.TryGetBulletsPoint(frameSync.mutable_bullets());
	Message.SendMsg(INVALID_CHAIR, MSG_S_FrameSync, &frameSync);
}
