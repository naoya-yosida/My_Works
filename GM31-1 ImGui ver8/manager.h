#pragma once

class Manager
{
private:
	static class Scene*m_Scene;
public:
	static void Init();//初期化
	static void Uninit();//終了
	static void Update();//更新
	static void Draw();//描画

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