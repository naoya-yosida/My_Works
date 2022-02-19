#pragma once
#include "game_object.h"
class MeshField :public GameObject
{
private:
	ID3D11Buffer*             m_VertexBuffer = NULL;//���_�o�b�t�@
	ID3D11Buffer*             m_IndexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;   //�e�N�X�`��

	VERTEX_3D  m_Vertex[21][21];

	ID3D11VertexShader*       m_VertexShader = NULL;     //
	ID3D11PixelShader*        m_PixelShader = NULL;      //
	ID3D11InputLayout*        m_VertexLayout = NULL;     //

public:
	//�����o�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(D3DXVECTOR3 Position);
};//�N���X�̍Ō��;�t����