#pragma once

#include "Wrapper.h"
#include "helpers.h"
#include "ClientHelper.h"

namespace UnityEngine {
	namespace GameObject {
		app::Component* GetComponentByName(app::GameObject* go, const char* type);
		app::Component__Array* LogComponents(app::GameObject* go);
	}

	namespace Math {
		namespace Vector3 {
			const char* ToString(app::Vector3* v);
			const char* ToString(app::Vector3 v);
		}
	}

	namespace Transform {
		app::Transform* Get(app::GameObject* go);
		app::Vector3 Position(app::Transform* transform);
	}

	struct Object {

		static const char* GetObjectName(app::Object_1* obj);

		static app::GameObject__Array* FindGameObjectsWithTag(const char* tag);

		// Object_1_FindObjectFromInstanceID
		static void FindObjectFromInstanceID(int32_t instanceID);

		template<typename T>
		static T* FindObjectOfType(const char* className, const char* classNamespace = "", const char* assemblyName = "Assembly-CSharp.dll") {

			Wrapper obj(assemblyName);

			Il2CppObject* object = obj.find_class(classNamespace, className).get_class();

			if (!object || !app::Object_1_FindObjectOfType) return nullptr;

			app::Object_1* obj_1 = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

			if (!obj_1 || IsNull(obj_1)) return nullptr;

			return reinterpret_cast<T*>(obj_1);
		}
		
	};
}
