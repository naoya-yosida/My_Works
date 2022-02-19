#include "main.h"
#include "manager.h"
#include "renderer.h"
//#include "model.h"
#include "debug_camera.h"
#include "input.h"
#include "player.h"
#include "scene.h"
void DebugCamera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void DebugCamera::Uninit()
{
}

void DebugCamera::Update()
{
	//Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	//m_Target = player->GetPosition();

	//トップビュー
	//m_Position = m_Target + D3DXVECTOR3(0.0f, 1.3f, -2.5f);

	//サードパーソンビュー
	D3DXVECTOR3 forward = GetForward();
	//m_Position = m_Target - forward * 7.0f + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	if (Input::GetKeyPress(VK_LEFT))
	{
		m_Rotation.y -= 0.05f;
	}
	if (Input::GetKeyPress(VK_RIGHT))
	{
		m_Rotation.y += 0.05f;
	}
	if (Input::GetKeyPress(VK_UP))
	{
		m_Rotation.x -= 0.05f;
		if (m_Rotation.x < -0.08f)
		{
			m_Rotation.x = -0.08f;
		}
	}
	if (Input::GetKeyPress(VK_DOWN))
	{
		m_Rotation.x += 0.05f;
		if (m_Rotation.x > 0.5f)
		{
			m_Rotation.x = 0.5f;
		}
	}
	if (Input::GetKeyPress('U'))
	{
		m_Position.x += 0.05f;
	}
	if (Input::GetKeyPress('J'))
	{
		m_Position.x -= 0.05f;
	}
	if (Input::GetKeyPress(VK_SPACE))
	{
		m_Position.y += 0.05f;
	}
	if (Input::GetKeyPress(VK_CONTROL))
	{
		m_Position.y -= 0.05f;
	}
}

void DebugCamera::Draw()
{
	//ビューマトリックス設定
	//D3DXMATRIX viewMatrix;//ローカル変数
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	Renderer::SetViewMatrix(&m_ViewMatrix);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = rot * trans;
	Renderer::SetWorldMatrix(&world);

	//プロジェクトマトリックス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
