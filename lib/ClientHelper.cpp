#include "pch-il2cpp.h"

#include "helpers.h"

#include "ClientHelper.h"
#include "wrapper.h"

bool IsSinglePlayer()
{
	return app::BoltNetwork_get_IsSinglePlayer(NULL);
}

bool IsOnline()
{
	return not app::BoltNetwork_get_IsSinglePlayer(NULL);
}

bool IsHost()
{
	return app::BoltNetwork_get_IsServer(NULL);
}

app::Menu* get_HorrorMenu() {
	Wrapper wrapper;

	const Il2CppImage* image = wrapper.GetImage("Assembly-CSharp.dll");

	// DO_APP_FUNC(0x0065B240, void, Menu_OnLobbyStartButtonClick, (Menu * __this, MethodInfo * method));
	// menu.OnLobbyStartButtonClick();

	Il2CppObject* object = wrapper.GetObjectFromClass(image, "Horror", "Menu");

	if (object != nullptr) {

		app::Object_1* Horror_MenuObject = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

		if (Horror_MenuObject) {
			app::Menu* HorrorMenu = reinterpret_cast<app::Menu*>(Horror_MenuObject);

			if (HorrorMenu) {
				return HorrorMenu;
			}
		}
	}

	return nullptr;
}

std::string get_SceneName()
{
	app::SaveHelpers* SaveHelper = app::SaveHelpers_get_singleton(nullptr);

	if (SaveHelper) {

		std::string str = il2cppi_to_string(SaveHelper->fields.sceneName);

		return str;
	}

	return std::string("unknown");
}
