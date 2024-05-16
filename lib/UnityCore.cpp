#include "pch-il2cpp.h"

#include "UnityCore.h"

app::Component* Unity::GameObject::GetComponentByName(app::GameObject* go, const char* type)
{
	app::String* str = reinterpret_cast<app::String*>(il2cpp_string_new(type));

	if (str != nullptr) {
		app::Component* component = app::GameObject_GetComponentByName(go, str, nullptr);

		if (component != nullptr) {
			return component;
		}
	}

	return nullptr;
}
