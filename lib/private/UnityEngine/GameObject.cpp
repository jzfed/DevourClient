#include "pch-il2cpp.h"

#include "UnityEngine/GameObject.h"

#include "wrapper.h"
#include <helpers.h>

app::Component* GameObject::GetComponentByName(app::GameObject* go, const char* type)
{
	app::Component* component = app::GameObject_GetComponentByName(go, ConvertToSystemString(type), nullptr);

	return component ? component : nullptr;
}

app::Component__Array* GameObject::LogComponents(app::GameObject* go)
{
	Wrapper obj("UnityEngine.CoreModule.dll");

	Il2CppObject* object = obj.find_class("UnityEngine", "Component").get_class();

	if (!object) return nullptr;

	app::Type* type = reinterpret_cast<app::Type*>(object);
	if (!type) return nullptr;

	app::Component__Array* __components = app::GameObject_GetComponents(go, type, nullptr);

	return __components ? __components : nullptr;
}
