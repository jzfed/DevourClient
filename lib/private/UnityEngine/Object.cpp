#include "pch-il2cpp.h"

#include "UnityEngine/Object.h"
#include <string>
#include <helpers.h>

const char* Object::GetObjectName(app::Object_1* obj)
{
	static std::string name = il2cppi_to_string(app::Object_1_GetName(obj, nullptr));
	return name.c_str();
}

app::GameObject__Array* Object::FindGameObjectsWithTag(const char* tag)
{
	app::GameObject__Array* go_array_result = app::GameObject_FindGameObjectsWithTag(ConvertToSystemString(tag), nullptr);

	return go_array_result ? go_array_result : nullptr;
}

void Object::FindObjectFromInstanceID(int32_t instanceID)
{
}

bool Object::IsNull(app::Object_1* obj)
{
	if (obj == nullptr)
		return true;
	
	return !app::Object_1_op_Implicit(obj, nullptr);
}
