#pragma once

class GameObject
{
protected://�p����̃N���X����̓A�N�Z�X�ł���
	bool m_Destroy = false;
	//�����o�ϐ�
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
	float m_fov;

public:
	GameObject() {}//�R���X�g���N�^ {}=���g��
	virtual ~GameObject() {}//�f�X�g���N�^(���z�֐�) 

	//�����o�֐�
	virtual void Init()=0;//virtual = �������z�֐�...�\������炵��
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;

	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}
	void SetDestroy(){ m_Destroy = true; }
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
};