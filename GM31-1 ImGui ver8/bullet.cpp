#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "model.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "explosion.h"

Model*Bullet::m_Model;//staticメンバ変数はcppで再宣言
ID3D11VertexShader*Bullet::m_VertexShader;
ID3D11PixelShader*Bullet::m_PixelShader;
ID3D11InputLayout*Bullet::m_VertexLayout;

void Bullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}
void Bullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 4.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
}
void Bullet::Uninit()
{
	
}
void Bullet::Update()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	D3DXVECTOR3 oldforward = player->GetForward();
	
	Scene*scene = Manager::GetScene();

	m_Position += oldforward * 0.5f;
	if (m_Position.z > 100.0f)
	{
		scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
		SetDestroy();
		return;
	}
	else if (m_Position.z < -100.0f)
	{
		scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);

		SetDestroy();
		return;
	}
	else if (m_Position.x > 100.0f)
	{
		scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);

		SetDestroy();
		return;
	}
	else if (m_Position.x < -100.0f)
	{
		scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);

		SetDestroy();
		return;
	}

	std::vector<Enemy*>enemyList = scene->GetGameObjects<Enemy>(1);

	for (Enemy*enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 2.0f)
		{
			scene->AddGameObject<Explosion>(1)->SetPosition(enemyPosition);

			enemy->SetDestroy();
			SetDestroy();
			return;
		}
	}
}
void Bullet::Draw()
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
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}