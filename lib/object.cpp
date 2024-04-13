#include "pch-il2cpp.h"

#include "object.h"
#include "helpers.h"

app::GameObject* GameObject::FindWithTag(const char* tag)
{
	Il2CppString* newStr = il2cpp_string_new(tag);
	app::String* convert_to_appString = reinterpret_cast<app::String*>(newStr);

	if (app::GameObject_FindWithTag(convert_to_appString, nullptr)) {
		return app::GameObject_FindWithTag(convert_to_appString, nullptr);
	}

	return nullptr;
}

template<typename T>
inline T* GameObject::GetComponent()
{
	return nullptr;
}
