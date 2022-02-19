#pragma once
#include "game_object.h"
#include "audio.h"
class Player:public GameObject
{
private:
	class AnimationModel*m_Model;

	ID3D11VertexShader*       m_VertexShader = NULL;     //
	ID3D11PixelShader*        m_PixelShader = NULL;      //
	ID3D11InputLayout*        m_VertexLayout = NULL;     //
	float m_BlendRate;
	int m_Frame;
	bool m_Press;

	Audio* m_ShotSE;
public:
	//メンバ関数
	void Init();
	void Uninit();
	void Update();
	void Draw();
};//クラスの最後に;付ける