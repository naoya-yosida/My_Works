// ===================================
// imgui
// ===================================
#include "ImGui/imgui.h"
#include "ImGuizmo.h"
#include <d3d11.h>
#include <tchar.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_PLACEMENT_NEW
#include "ImGui/imgui_internal.h"

#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_stdlib.h"
class ImguiMain
{
private:
	float m_fov;
public:
	static void Init();//‰Šú‰»
	static void Uninit();//I—¹
	static void Update();//XV
	static void Draw();//•`‰æ
};