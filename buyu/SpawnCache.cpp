#include "SpawnCache.h"



SpawnCache::SpawnCache()
{
}


SpawnCache::~SpawnCache()
{
}
void SpawnCache::Bind(MessageModel* message) {
	Message = message;
}
void SpawnCache::Init() {
	//player
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			PlayerTeam,
			Vector3{ 10, 0, 10 },
			3,
			1,
			0,
			1,
			true,
			false,
			true,
			true,
			false,
			false,
			true,
			true,
			true,
			true,
			false
		);

		Dic.push_back(s);
	}


	//{
	//	//¹­¼ýÊÖ
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(15, 0, 20),
			102,
			1,
			5 * 60,
			1,
			true,
			false,
			true,
			true,
			true,
			true,
			false,
			false,
			false,
			false,
			true
		);

		Dic.push_back(s);
	}
	
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(20, 0, 20),
			102,
			1,
			5 * 60,
			1,
			true,
			false,
			true,
			true,
			true,
			true,
			false,
			false,
			false,
			false,
			true
		);

		Dic.push_back(s);
	}

	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(25, 0, 20),
			102,
			1,
			5 * 60,
			1,
			true,
			false,
			true,
			true,
			true,
			true,
			false,
			false,
			false,
			false,
			true
		);

		Dic.push_back(s);
	}
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(30, 0, 20),
			102,
			1,
			5 * 60,
			1,
			true,
			false,
			true,
			true,
			true,
			true,
			false,
			false,
			false,
			false,
			true
		);

		Dic.push_back(s);
	}
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(35, 0, 20),
			102,
			1,
			5 * 60,
			1,
			true,
			false,
			true,
			true,
			true,
			true,
			false,
			false,
			false,
			false,
			true
		);

		Dic.push_back(s);
	}
	//}
	
	//boss
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(10, 0, 7), 
			101, 
			1, 
			5 * 60, 
			1, 
			true, 
			true, 
			true, 
			true, 
			true, 
			true, 
			false,
			false,
			false,
			false,
			true
			);

		Dic.push_back(s);
	}
	
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(10, 0, 7),
			103,
			50,
			5 * 60,
			5,
			true,
			true,
			false,
			true,
			false,
			true,
			false,
			false,
			false,
			false,
			true
		);

		Dic.push_back(s);
	}
	{
		SpawnModel s;
		s.Bind(Message);
		s.Init(
			Dic.size(),
			MonsterTeam,
			Vector3(10, 0, 6),
			104,
			50,
			5 * 60,
			1,
			true,
			true,
			false,
			true,
			false,
			true,
			false,
			false,
			false,
			false,
			true
		);

		Dic.push_back(s);
	}
	
}
void SpawnCache::Update(int frame) {
	
	for (auto& spawn : Dic) {
		spawn.Update(frame);
	}
}