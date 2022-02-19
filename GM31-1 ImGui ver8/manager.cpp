#include "main.h"
#include "manager.h"
#include "imgui_main.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "audio.h"


Scene*Manager::m_Scene = NULL;


void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	//Audio::InitMaster();
	SetScene<Game>();
	ImguiMain::Init();
}	


void Manager::Uninit()
{	
	ImguiMain::Uninit();
	m_Scene->Uninit();
	delete m_Scene;
	//Audio::UninitMaster();
	Input::Uninit();
    Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();
	m_Scene->Update();
	ImguiMain::Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();
	ImguiMain::Draw();

	Renderer::End();
}
