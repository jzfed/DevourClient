#pragma once

#include <map>

class Wrapper {
public:
	Wrapper();

	const Il2CppAssembly* GetAssembly(const char* _assembly);
	const Il2CppImage* GetImage(const char* _assembly);

	Il2CppObject* GetObjectFromClass(const Il2CppImage* _image, const char* _namespaze, const char* _name);
private:
	std::map<const char*, const Il2CppAssembly*> assemblyMap;
};
