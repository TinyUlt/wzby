
#include<iostream>
#include <fstream>
#include <string>
#include <map>
#include "Global.h"
// void InitServerConfig(string fname);
void InitGameConfig(string fname);
void InitCollider(string fname);
void InitPathLogic(string fname);
void InitPath(string fname);


void main(){
	cout << "hello world" << endl;

	g_Global.InterestRate = 1000;
	g_Global.TestFishPosition = false;
// 	InitServerConfig("conf/ServerConfig.json");
 	InitGameConfig("C:/Users/Administrator/Desktop/buyu/Debug/conf/GameConfig.bytes");
 	InitCollider("C:/Users/Administrator/Desktop/buyu/Debug/conf/Collider.bytes");
 	InitPath("C:/Users/Administrator/Desktop/buyu/Debug/conf/OriginPathFile_Server.bytes");
 	InitPathLogic("C:/Users/Administrator/Desktop/buyu/Debug/conf/ProductLogic.bytes");
}

void InitGameConfig(string fname){
	fstream input(fname, ios::in | ios::binary);
	if (!input){
		return;
	}

	g_Global.GlobalGameConfig.ParseFromIstream(&input);

	//添加倍数逻辑
	{
		int muls[] = { 100, 200, 300, 400, 500, 1100, 1200, 1300, 1400, 1500 };
		float mulCount = countof_macro(muls);
		float originCount = float(g_Global.GlobalGameConfig.bulletconfigs_size());
		float step = originCount / mulCount;
		auto bulletconfig = g_Global.GlobalGameConfig.bulletconfigs();
		g_Global.GlobalGameConfig.clear_bulletconfigs();

		for (int j = 0; j < mulCount; j++) {

			int s = (int)(step * (float)j);

			auto bulletData = g_Global.GlobalGameConfig.add_bulletconfigs();
	
			bulletData->set_model(bulletconfig.Get(s).model());
			bulletData->set_speed(bulletconfig.Get(s).speed());
			bulletData->set_radius(bulletconfig.Get(s).radius());
			bulletData->set_yuwangmodel(bulletconfig.Get(s).yuwangmodel());
			bulletData->set_turretmodel(bulletconfig.Get(s).turretmodel());
			bulletData->set_type(j);
			bulletData->set_multiple(muls[j]);

	
			cout << bulletData->model() << endl;
		}
	}

	//技能子弹配置
	{
		int muls[] ={6000, 7000, 8000, 9000};
		int len = countof_macro(muls);
		for (int j = 0; j < len; j++){

			if (j < g_Global.GlobalGameConfig.instantconfigs_size()) {
				auto ins = g_Global.GlobalGameConfig.instantconfigs(j);
				ins.set_multiple(muls[j]);
			}
		}
	}
}

void InitCollider(string fname){
	fstream input(fname, ios::in | ios::binary);
	FishColliderGroup fc;
	fc.ParseFromIstream(&input);
	for (int i = 0; i < fc.colliderlist_size(); ++i)
	{
		auto collider = fc.colliderlist(i);

		g_Global.FishColliderList[collider.fishname()] = collider;
	}
}

void InitPath(string fname){

	fstream input(fname, ios::in | ios::binary);
	PathGroupServer pg;
	pg.ParseFromIstream(&input);
	auto size = pg.pathlist_size();
	for (int i = 0; i < pg.pathlist_size(); ++i)
	{
		SinglePathServer singlePath = pg.pathlist(i);
		auto pathPointList = singlePath.pathpointlist();
		g_Global.SavePath[singlePath.pathname()] = pathPointList;
	}
}
void InitPathLogic(string fname){

	fstream input(fname, ios::in | ios::binary);

	g_Global.ProductItemStore.ParseFromIstream(&input);
}