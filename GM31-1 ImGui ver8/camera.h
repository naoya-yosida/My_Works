#pragma once
#include "game_object.h"
class Camera:public GameObject
{
private:
	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
	float m_fov;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	float GetFov(float fov) { return m_fov; }
};