#include "pch-il2cpp.h"
#include "utils.hpp"
#include "helpers.h"

std::string ToString(app::Object* object) {
	std::string type = il2cppi_to_string(app::Object_ToString(object, NULL));
	if (type == "System.String") {
		return il2cppi_to_string((app::String*)object);
	}
	return type;
}

