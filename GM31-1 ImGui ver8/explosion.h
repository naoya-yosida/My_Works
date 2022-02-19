#pragma once
#include "game_object.h"
class Explosion :public GameObject
{
private:
	ID3D11Buffer*             m_VertexBuffer = NULL;//頂点バッファ
	ID3D11ShaderResourceView* m_Texture = NULL;   //テクスチャ

	ID3D11VertexShader*       m_VertexShader = NULL;     //
	ID3D11PixelShader*        m_PixelShader = NULL;      //
	ID3D11InputLayout*        m_VertexLayout = NULL;     //
	int m_Count;
											
public:
	//メンバ関数
	void Init();
	void Uninit();
	void Update();
	void Draw();
};//クラスの最後に;付ける