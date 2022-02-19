#include "imgui_main.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "debug_camera.h"
#include "camera.h"
#include "player.h"
#include "wood.h"

static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static int counter = 0;
static int oldcounter = 0;
static int o = 0;
static D3DXVECTOR3 oldpos[10];
static bool show_player_window = true;
static bool show_demo_window = false;
static bool no_move = false;
static bool disable_mouse_wheel = true;
static bool debug_camera = false;
static bool mode_wireframe = NULL;
static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
static bool useSnap = false;
static float snap[3] = { 1.f, 1.f, 1.f };
static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
static bool boundSizing = false;
static bool boundSizingSnap = false;
static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);

void ImguiMain::Init()
{
	HWND hwnd = GetWindow();

	// Show the window
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	
	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(Renderer::GetDevice(), Renderer::GetDeviceContext());

	// Load Fonts
	ImFontConfig config;
	config.MergeMode = true;
	io.Fonts->AddFontDefault();
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	IM_ASSERT(font != NULL);

}

void ImguiMain::Uninit()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImguiMain::Update()
{
	// Imgui Start
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuizmo::BeginFrame();
	ImGuizmo::IsOver();
	ImGuizmo::IsUsing();
	ImGui::Begin("");                          // Create a window called "Hello, world!" and append into it.
	ImGuiWindowFlags window_flags = 0;
	if (ImGui::TreeNode("PlayerState"))
	{
		//プレイヤーのステータス
		Scene* scene = Manager::GetScene();
		Player* player = scene->GetGameObject<Player>(1);
		D3DXVECTOR3 playerPos = player->GetPosition();
		D3DXVECTOR3 playerRot = player->GetRotation();
		D3DXVECTOR3 playerScl = player->GetScale();
		ImGui::Text("[PlayerPos.x %.1f][PlayerPos.y %.1f][PlayerPos.z %.1f]", playerPos.x, playerPos.y, playerPos.z);
		ImGui::Text("[PlayerRot.x %.1f][PlayerRot.y %.1f][PlayerRot.z %.1f]", playerRot.x, playerRot.y, playerRot.z);
		ImGui::Text("[PlayerScale.x %.2f][PlayerScale.y %.2f][PlayerScale.z %.2f]", playerScl.x, playerScl.y, playerScl.z);
	}
	static float wx,wy,wz;
	static float m_fov = 1.0f;
	static float slider_f = 0.5f;
	static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	if (ImGui::TreeNode("Object"))
	{
		//縦画面スクロール
		window_flags = ImGuiWindowFlags_HorizontalScrollbar;
		ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y * 0.3f), false, window_flags);
		for (int i = 0;i < counter;i++) {
			ImGui::Text("GameObject<Wood>(%d):[pos.x %.1f][pos.y %.1f][pos.z %.1f] ", i, oldpos[i + 1].x, oldpos[i + 1].y, oldpos[i + 1].z);
		}
		ImGui::EndChild();

		ImGui::DragFloat("WoodPos.x", &wx, 1.0f, -1000.0f, 1000.0f, "%.1f", flags);
		ImGui::DragFloat("WoodPos.y", &wy, 1.0f, 0.0f, 1000.0f, "%.1f", flags);
		ImGui::DragFloat("WoodPos.z", &wz, 1.0f, -1000.0f, 1000.0f, "%.1f", flags);
		//オブジェクト追加
		if (ImGui::Button("addit"))
		{
			counter++;

			Scene* scene = Manager::GetScene();
			scene->AddGameObject<Wood>(1)->SetPosition(D3DXVECTOR3(wx, wy, wz));
			for (int i = 0;i < counter;i++) {
				oldpos[counter] = D3DXVECTOR3(wx, wy, wz);
			}
		}
	}
	if (ImGui::TreeNode("Setting"))
	{
		ImGui::DragFloat("Fov", &m_fov, 0.01f, 0.01f, 3.0f, "%.2f", flags);
		//プロジェクトマトリックス設定
		D3DXMATRIX projectionMatrix;
		Scene* scene = Manager::GetScene();
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, m_fov, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

		Renderer::SetProjectionMatrix(&projectionMatrix);
	}

	//ImGui::Separator();
	if(ImGui::RenderFrame)
		
		if (ImGui::BeginTable("split", 3))//横並びを有効にする　数字は横に並べる個数を決めれる
		{
			ImGui::TableNextColumn(); ImGui::Checkbox("Demo Window", &show_demo_window);//demomode切り替え
			ImGui::TableNextColumn(); ImGui::Checkbox("No move", &no_move);	
			ImGui::TableNextColumn(); ImGui::Checkbox("Debug Camera", &debug_camera);	
			ImGui::EndTable();
		}
		//ImGui::Checkbox("Player Window", &show_player_window);
		ImGui::Checkbox("WireFrameMode", &mode_wireframe);//wireframe切り替え
		if (mode_wireframe == true)
		{
			Renderer::MW();
		}
		else
		{
			Renderer::MWN();
		}
		if (show_demo_window)
		{
			ImGui::ShowDemoWindow(&show_demo_window);
		}
		
	/*	if (debug_camera)
		{
			Scene* scene = Manager::GetScene();
			scene->AddGameObject<DebugCamera>(0)->SetPosition(D3DXVECTOR3(0,5.0f,0));
		}*/
	
		/*if (no_move)
		{
			window_flags |= ImGuiWindowFlags_NoMove;
		}*/
	//フレームレート
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void ImguiMain::Draw()
{
	// Rendering
	ImGui::Render();
	//ImGuizmo::DrawGrid(&g_mainRenderTargetView, Camera::, identityMatrix, 100.f);
	const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    //g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    //g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	//g_pSwapChain->Present(1, 0);
}


