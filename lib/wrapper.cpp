#include "pch-il2cpp.h"

#include "wrapper.h"

#include <iostream>

Wrapper::Wrapper()
{
	const Il2CppDomain* domain = il2cpp_domain_get();

	const Il2CppAssembly** assemblies;
	size_t size;

	assemblies = il2cpp_domain_get_assemblies(domain, &size);

	assemblyMap.clear();

	for (size_t i = 0; i < size; ++i) {
		const Il2CppAssembly* assembly = assemblies[i];

		if (assembly) {
			const char* assemblyName = il2cpp_image_get_name(assembly->image);
			assemblyMap[assemblyName] = assembly;
			std::cout << "\t- " << assemblyName << std::endl;
		}
	}
}


const Il2CppAssembly* Wrapper::GetAssembly(const char* _assembly) {
	for (const auto& entry : assemblyMap) {
		if (strcmp(entry.first, _assembly) == 0) {
			return entry.second;
		}
	}
	return nullptr;
}

const Il2CppImage* Wrapper::GetImage(const char* _assembly) {
	for (const auto& entry : assemblyMap) {
		if (strcmp(entry.first, _assembly) == 0) {
			return entry.second->image;
		}
	}

	return nullptr;
}

Il2CppObject* Wrapper::GetObjectFromClass(const Il2CppImage* _image, const char* _namespaze, const char* _name)
{
	return nullptr;
}
