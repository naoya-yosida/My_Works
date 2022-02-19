#pragma once
#include "game_object.h"
class Bullet :public GameObject
{
private:
	static Model*m_Model;//static������ƃO���[�o���ϐ��̂悤�Ȉ��������ł���

	static ID3D11VertexShader*       m_VertexShader;     
	static ID3D11PixelShader*        m_PixelShader;     
	static ID3D11InputLayout*        m_VertexLayout;     
public:
	static void Load();
	static void Unload();
	//�����o�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();
};//�N���X�̍Ō��;�t����