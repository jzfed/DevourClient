#pragma once

#include "Wrapper.h"
#include <vector>
#include <iostream>
#include "ClientHelper.h"

namespace Unity {
	namespace GameObject {
		// DO_APP_FUNC(0x02D34DA0, Component *, GameObject_GetComponentByName, (GameObject * __this, String * type, MethodInfo * method));
		app::Component* GetComponentByName(app::GameObject* go, const char* type);
	}

	namespace Math {
		namespace Vector3 {
			std::string ToString(app::Vector3* v);
			std::string ToString(app::Vector3 v);
		}
	}

	namespace Transform {
		app::Transform* Get(app::GameObject* go);
		app::Vector3 Position(app::Transform* transform);
	}
}

namespace UnityCore {
	template<typename T>
	class Object {
	public:
		Object() = default;

		static T* FindObjectOfType(const char* className, const char* classNamespace = "");
	};

	template<typename T>
	inline T* Object<T>::FindObjectOfType(const char* className, const char* classNamespace)
	{
		Wrapper obj("Assembly-CSharp.dll");

		Il2CppObject* object = obj.find_class(classNamespace, className).get_class();
		if (object) {

			if (app::Object_1_FindObjectOfType == nullptr) return nullptr;

			app::Object_1* obj_1 = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

			if (IsNull(obj_1) || obj_1 == nullptr) return nullptr;

			T* foundObject = reinterpret_cast<T*>(obj_1);

			if (foundObject) {
				return foundObject;
			}
		}

		return nullptr;
	}
}
