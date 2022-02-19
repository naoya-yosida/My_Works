#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "titlelogo.h"
#include "game.h"
#include "input.h"

void Title::Init()
{
	AddGameObject<TitleLogo>(2);
}
void Title::Uninit()
{
	Scene::Uninit();
}
void Title::Update()
{
	Scene::Update();
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Manager::SetScene<Game>();
	}
}
