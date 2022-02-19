#pragma once
#include "game_object.h"
class DebugCamera :public GameObject
{
private:
	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
};