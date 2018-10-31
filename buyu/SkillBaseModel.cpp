#include "SkillBaseModel.h"
#include "ItemCache.h"


SkillBaseModel::SkillBaseModel()
{
}


SkillBaseModel::~SkillBaseModel()
{
}
void SkillBaseModel::Bind(ItemModel* host, ItemCache* itemManager, MessageModel* message) {
	Host = host;
	Message = message;
	ItemManager = itemManager;
}
void SkillBaseModel::Update(int frame) {
	NowFrame = frame;
}