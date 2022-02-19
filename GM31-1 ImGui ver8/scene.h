#pragma once

#include<list>
#include<vector>
#include<typeinfo>
#include"game_object.h"

class Scene
{
protected:
	std::list<GameObject*> m_GameObject[10];//STL�̃��X�g�\��...�z���胊�X�g�\���̂ق����ォ��ǉ��Ȃǂ��₷��
	                                       //���X�g�\����z��ɂ���
public:
	Scene() {}
	virtual~Scene() {}

	//�����o�֐�
	virtual void Init() = 0;//scene�̂Ȃ��ł͎g��Ȃ��̂�=0�t���ď������z�֐��ɂ���

	virtual void Uninit()
	{
		for (int i = 0;i < 10;i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;//���g����
			}
			m_GameObject[i].clear();//���X�g���̏���
		}
	}
	virtual void Update()
	{
		for (int i = 0;i < 10;i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}
			m_GameObject[i].remove_if([](GameObject*object) {return object->Destroy();});//�����_���������Έ����ɒ��ڊ֐�������邱�Ƃ��ł���
		}
	}
	virtual void Draw()
	{
		for (int i = 0;i < 10;i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	template<typename T>//�e���v���[�g�֐�
	T*AddGameObject(int Layer)
	{
		T*gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
        gameObject->Init();

		return gameObject;
	}

	template<typename T>//�e���v���[�g�֐�
	T*GetGameObject(int Layer)//1�����i�[�ł��Ȃ�
	{
		for (GameObject*object : m_GameObject[Layer])
			if (typeid(*object) == typeid(T))//�^�𒲂ׂ�
			{
				return(T*)object;//�������烊�^�[��
			}
		return NULL;
	}

	template<typename T>//�e���v���[�g�֐�
	std::vector<T*>GetGameObjects(int Layer)//�����������
	{
		std::vector<T*>objects;//STL�̔z��
		for (GameObject*object : m_GameObject[Layer])
			if (typeid(*object) == typeid(T))////�^�𒲂ׂ�
			{
				objects.push_back((T*)object);//�݂�����V�������X�g�\���ɒǉ�
			}
		return objects;
	}
};