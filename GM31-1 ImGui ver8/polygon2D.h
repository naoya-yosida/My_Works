#pragma once
#include "game_object.h"
class Polygon2D :public GameObject
{
private:
	//�����o�ϐ�
	ID3D11Buffer*             m_VertexBuffer = NULL;//���_�o�b�t�@
	ID3D11ShaderResourceView* m_Texture      = NULL;   //�e�N�X�`��

	ID3D11VertexShader*       m_VertexShader = NULL;     //
	ID3D11PixelShader*        m_PixelShader  = NULL;      //
	ID3D11InputLayout*        m_VertexLayout = NULL;     //

public:
	//Polygon2D();//�R���X�g���N�^
	//~Polygon2D();//�f�X�g���N�^
	//�����o�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();
};//�N���X�̍Ō��;�t����