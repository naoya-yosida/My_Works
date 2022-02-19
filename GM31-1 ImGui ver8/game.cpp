#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "camera.h"
#include "debug_camera.h"
#include "meshfield.h"
#include "sky.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "polygon2D.h"
#include "score.h"
//#include "audio.h"
#include "result.h"
#include "input.h"
#include "wood.h"
#include "imgui_main.h"

void Game::Init()
{
	Bullet::Load();
	AddGameObject<Camera>(0);
	//AddGameObject<DebugCamera>(0);
	AddGameObject<MeshField>(1);
	AddGameObject<Sky>(1);
	AddGameObject<Player>(1);

	//Enemy*enemy=AddGameObject<Enemy>();//3体分の敵
	//enemy->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 5.0f));
	//AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-5.0f, 1.0f, 5.0f));//うえの2行を1行に
	//AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 5.0f));
	//AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(5.0f, 1.0f, 5.0f));
	//AddGameObject<Bullet>();
	//AddGameObject<Explosion>(1);
	//AddGameObject<Score>(2);
	//AddGameObject<Polygon2D>(2);

	//Audio *bgm = AddGameObject<Audio>(2);
	//bgm->Load("asset\\audio\\ロックbgm.wav");
	//bgm->Play(true);
}
void Game::Uninit()
{
	Scene::Uninit();//継承元クラスのメソッド呼び出し
	Bullet::Unload();
}

void Game::Update()
{
	Scene::Update();
	std::vector<Enemy*>enemyList = GetGameObjects<Enemy>(1);
	if (enemyList.size()==0)
	{
		//Manager::SetScene<Result>();
	}
}