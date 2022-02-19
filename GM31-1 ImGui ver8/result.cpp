#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "result.h"
#include "resultlogo.h"
#include "input.h"
#include "title.h"

void Result::Init()
{
	AddGameObject<ResultLogo>(2);
}
void Result::Uninit()
{
	Scene::Uninit();
}
void Result::Update()
{
	Scene::Update();
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Manager::SetScene<Title>();
	}
}