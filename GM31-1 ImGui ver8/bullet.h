#pragma once
#include "game_object.h"
class Bullet :public GameObject
{
private:
	static Model*m_Model;//staticをつけるとグローバル変数のような扱い方ができる

	static ID3D11VertexShader*       m_VertexShader;     
	static ID3D11PixelShader*        m_PixelShader;     
	static ID3D11InputLayout*        m_VertexLayout;     
public:
	static void Load();
	static void Unload();
	//メンバ関数
	void Init();
	void Uninit();
	void Update();
	void Draw();
};//クラスの最後に;付ける