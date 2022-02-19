#pragma once

#include<list>
#include<vector>
#include<typeinfo>
#include"game_object.h"

class Scene
{
protected:
	std::list<GameObject*> m_GameObject[10];//STLのリスト構造...配列よりリスト構造のほうが後から追加などしやすい
	                                       //リスト構造を配列にする
public:
	Scene() {}
	virtual~Scene() {}

	//メンバ関数
	virtual void Init() = 0;//sceneのなかでは使わないので=0付けて純粋仮想関数にする

	virtual void Uninit()
	{
		for (int i = 0;i < 10;i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;//中身消す
			}
			m_GameObject[i].clear();//リスト自体消す
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
			m_GameObject[i].remove_if([](GameObject*object) {return object->Destroy();});//ラムダ式をつかえば引数に直接関数をいれることができる
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

	template<typename T>//テンプレート関数
	T*AddGameObject(int Layer)
	{
		T*gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
        gameObject->Init();

		return gameObject;
	}

	template<typename T>//テンプレート関数
	T*GetGameObject(int Layer)//1個しか格納できない
	{
		for (GameObject*object : m_GameObject[Layer])
			if (typeid(*object) == typeid(T))//型を調べる
			{
				return(T*)object;//見つけたらリターン
			}
		return NULL;
	}

	template<typename T>//テンプレート関数
	std::vector<T*>GetGameObjects(int Layer)//複数入れられる
	{
		std::vector<T*>objects;//STLの配列
		for (GameObject*object : m_GameObject[Layer])
			if (typeid(*object) == typeid(T))////型を調べる
			{
				objects.push_back((T*)object);//みつけたら新しいリスト構造に追加
			}
		return objects;
	}
};