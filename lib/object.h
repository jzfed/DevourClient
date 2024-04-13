#pragma once



class GameObject {
public:
	GameObject() = default;

	app::GameObject* FindWithTag(const char* tag);

	template<typename T>
	T* GetComponent();
private:
	app::GameObject* _currentGameObject = nullptr;
};

