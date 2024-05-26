#include "pch-il2cpp.h"
#include "utils.hpp"
#include "helpers.h"
#include <map>
#include <fstream>
#include <sstream>
#include <Windows.h>

int GetKey(KeyCode code)
{
	return static_cast<int>(code);
}

bool GetKeyDown(KeyCode key)
{
	// Convert KeyCode enum value to virtual keycode
	int vkey = GetKey(key);

	// Check key state with GetKeyState
	return (GetKeyState(vkey) & 0x8000) != 0;
}

bool GetKeyDownAsync(KeyCode key) {
	// Convert KeyCode enum value to virtual keycode
	int vkey = GetKey(key);

	// Check key state with GetAsyncKeyState
	return (GetAsyncKeyState(vkey) & 0x8000) != 0;
}

std::string ToString(app::Object* object) {
	std::string type = il2cppi_to_string(app::Object_ToString(object, NULL));
	if (type == "System.String") {
		return il2cppi_to_string((app::String*)object);
	}
	return type;
}

std::string ReadValueFromIni(const std::string& filename, const std::string& key, const std::string& defaultValue)
{
	std::ifstream file(filename);
	std::string line, value = defaultValue;

	if (file.is_open()) {
		while (getline(file, line)) {
			std::istringstream is_line(line);
			std::string currentKey;
			if (getline(is_line, currentKey, '=')) {
				std::string currentValue;
				if (getline(is_line, currentValue)) {
					if (currentKey == key) {
						value = currentValue;
						break;
					}
				}
			}
		}
		file.close();
	}
	else {
		// Create if file does not exist
		std::ofstream outFile(filename);
		outFile.close();
	}

	return value;
}



