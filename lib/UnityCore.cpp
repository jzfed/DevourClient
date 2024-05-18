#include "pch-il2cpp.h"

#include "UnityCore.h"
#include <helpers.h>

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

std::string Unity::Math::Vector3::ToString(app::Vector3* v)
{
	app::String* str = app::Vector3_ToString(v, nullptr);

	if (str == NULL) {
		return std::string("NULL");
	}

	return il2cppi_to_string(str);
}

std::string Unity::Math::Vector3::ToString(app::Vector3 v)
{
	return ("x: " + std::to_string(v.x) + " y: " + std::to_string(v.y) + " z: " + std::to_string(v.z));
}


app::Transform* Unity::Transform::Get(app::GameObject* go)
{
	if (go != nullptr) {
		if (app::GameObject_get_transform != nullptr) {

			app::Transform* __transform = app::GameObject_get_transform(go, nullptr);

			if (__transform) {
				return __transform;
			}
		}
	}

	return nullptr;
}

app::Vector3 Unity::Transform::Position(app::Transform* transform)
{
	if (transform != nullptr) {
		if (app::Transform_get_position != nullptr) {
			return app::Transform_get_position(transform, nullptr);
		}
	}
	
	return app::Vector3();
}
