#include "main.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "manager.h"
#include "player.h"
#include "scene.h"
//#include "bullet.h"
#include "meshfield.h"
#include "animationmodel.h"
#include "game_object.h"

//#include "audio.h"
void Player::Init()
{
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Akai_Idle.fbx");
	m_Model->Load("asset\\model\\Akai_Run.fbx");
	m_Model->LoadAnimation("asset\\model\\Akai_Idle.fbx","Idle");
	m_Model->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");
    m_Model->LoadAnimation("asset\\model\\Idle.fbx", "Crouch");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, -3.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	Scene*scene = Manager::GetScene();
	//m_ShotSE = scene->AddGameObject<Audio>(2);
	//m_ShotSE->Load("asset\\audio\\玉音.wav");
	//D3DXQuaternionIdentity(&m_Quaternion);
	m_BlendRate = 0;
	m_Frame = 0;
	m_Press = false;
}
void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}
void Player::Update()
{
	D3DXVECTOR3 forward = GetForward();
	m_Frame++;
	m_Model->Update("Idle", "Run", m_BlendRate, m_Frame);
	if (Input::GetKeyPress('W'))
	{
		m_Position -= forward * 0.1f;
		m_BlendRate += 0.1f;
		m_Press = true;
	}
	if (Input::GetKeyPress('S'))
	{
		m_Position += forward * 0.1f;
		m_BlendRate -= 0.1f;
		m_Press = true;
	}
	if (Input::GetKeyPress('A'))
	{
		m_Rotation.y -= 0.05f;
		m_BlendRate += 0.05f;
		m_Press = true;
	}
	if (Input::GetKeyPress('D'))
	{
		m_Rotation.y += 0.05f;
		m_BlendRate += 0.05f;
		m_Press = true;
	}
	else
	{
		m_Press = false;
	}
	if (m_Press ==false)
	{
		//m_Position.z -= 0.01f;
		m_BlendRate -= 0.05f;
	}
	if (m_BlendRate > 1.0f)
	{
		m_BlendRate = 1.0f;
	}
	if (m_BlendRate < 0.0f)
	{
		m_BlendRate = 0.0f;
	}

	MeshField*meshfield = Manager::GetScene()->GetGameObject<MeshField>(1);
	m_Position.y = meshfield->GetHeight(m_Position);
}
void Player::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//D3DXMatrixRotationQuaternion(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}


