#include "pch-il2cpp.h"

#include "UnityEngine/Input.h"
#include <helpers.h>

float Input::GetAxis(const char* axisName)
{
	return app::Input_1_GetAxis(ConvertToSystemString(axisName), nullptr);
}
