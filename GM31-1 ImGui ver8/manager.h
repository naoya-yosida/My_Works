#pragma once

class Manager
{
private:
	static class Scene*m_Scene;
public:
	static void Init();//‰Šú‰»
	static void Uninit();//I—¹
	static void Update();//XV
	static void Draw();//•`‰æ

	static class Scene* GetScene() { return m_Scene; }
	template<typename T>
	static void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		T*scene = new T();
		m_Scene = scene;
		scene->Init();
	}
};