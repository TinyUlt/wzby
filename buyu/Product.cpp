#include "Product.h"
#include "Global.h"
#include "LogSys.h"

//Product::Product()
//{
//}
//
//
//Product::~Product()
//{
//}
//
//void Product::Init() {
//	isProductDone = false;
//	nowProductIndex = 0;
//	nowFishPack = NULL;
//}
////void Product::Update(int frame) {
////
////	
////
////	TrySpawn(frame);
////}
//void Product::Change(int frame) {
//	//»ñÈ¡Ê§°Ü
//	if (!g_global.pathHelper->TryGetProducteFishList(producteFishList)) {
//
//		g_global.logSys->LogInWindow("change fail");
//	}
//	//producteFishList = PathCache.Instance.GetProducteFishList();
//	nowProductIndex = 0;
//	oldProductFrame = frame;
//	nowFishPack = &producteFishList[nowProductIndex];
//}
//bool Product::TrySpawn(int frame, vector<ProducteFishPack>& packList) {
//
//	if (nowFishPack == NULL)
//	{
//		Change(frame);
//	}
//
//	while ((&producteFishList[nowProductIndex])->Frame + oldProductFrame <= frame)
//	{
//		nowFishPack = &producteFishList[nowProductIndex];
//		auto pack = *nowFishPack;
//		pack.StartFrame = nowFishPack->Frame + oldProductFrame + 30;
//		packList.push_back(pack);
//		nowProductIndex++;
//		if (nowProductIndex >= producteFishList.size()) {
//			nowFishPack = NULL;
//			break;
//		}
//	}
//	if (packList.empty()) {
//		return false;
//	}
//	return true;
//}
