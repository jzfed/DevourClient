#include "pch-il2cpp.h"

#include "UnityEngine.h"
#include <helpers.h>

app::Component* UnityEngine::GameObject::GetComponentByName(app::GameObject* go, const char* type)
{
	app::Component* component = app::GameObject_GetComponentByName(go, ConvertToSystemString(type), nullptr);

	return component ? component : nullptr;
}

app::Component__Array* UnityEngine::GameObject::LogComponents(app::GameObject* go)
{
	Wrapper obj("UnityEngine.CoreModule.dll");

	Il2CppObject* object = obj.find_class("UnityEngine", "Component").get_class();

	if (!object) return nullptr;
	
	app::Type* type = reinterpret_cast<app::Type*>(object);
	if (!type) return nullptr;

	app::Component__Array* __components = app::GameObject_GetComponents(go, type, nullptr);

	return __components ? __components : nullptr;
}

const char* UnityEngine::Math::Vector3::ToString(app::Vector3* v)
{
	app::String* str = app::Vector3_ToString(v, nullptr);

	return str ? il2cppi_to_string(str).c_str() : "Vector::ToString returned nullptr!\n";
}

const char* UnityEngine::Math::Vector3::ToString(app::Vector3 v)
{
	return ("x: " + std::to_string(v.x) + " y: " + std::to_string(v.y) + " z: " + std::to_string(v.z)).c_str();
}

app::Transform* UnityEngine::Transform::Get(app::GameObject* go)
{
	if (!go || !app::GameObject_get_transform) return nullptr;

	app::Transform* __transform = app::GameObject_get_transform(go, nullptr);

	return __transform ? __transform : nullptr;
}

app::Vector3 UnityEngine::Transform::Position(app::Transform* transform)
{
	if (!transform || !app::Transform_get_position) return app::Vector3();
	
	return app::Transform_get_position(transform, nullptr);
}

app::Camera* UnityEngine::Camera::GetMainCamera() {
	return app::Camera_get_main(nullptr) ? app::Camera_get_main(nullptr) : nullptr;
}

const char* UnityEngine::Object::GetObjectName(app::Object_1* obj)
{
	static std::string name = il2cppi_to_string(app::Object_1_GetName(obj, nullptr));
	return name.c_str();
}

app::GameObject__Array* UnityEngine::Object::FindGameObjectsWithTag(const char* tag)
{
	app::GameObject__Array* go_array_result = app::GameObject_FindGameObjectsWithTag(ConvertToSystemString(tag), nullptr);

	return go_array_result ? go_array_result : nullptr;
}

void UnityEngine::Object::FindObjectFromInstanceID(int32_t instanceID)
{
}

float UnityEngine::Input::GetAxis(const char* axisName)
{
	return app::Input_1_GetAxis(ConvertToSystemString(axisName), nullptr);
}
