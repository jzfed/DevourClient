#include "pch-il2cpp.h"

#include "UnityEngine/Math.h"
#include <helpers.h>

const char* Math::Vector3::ToString(app::Vector3* v)
{
	app::String* str = app::Vector3_ToString(v, nullptr);

	return str ? il2cppi_to_string(str).c_str() : "Vector::ToString returned nullptr!\n";
}

const char* Math::Vector3::ToString(app::Vector3 v)
{
	return ("x: " + std::to_string(v.x) + " y: " + std::to_string(v.y) + " z: " + std::to_string(v.z)).c_str();
}
