#include "pch-il2cpp.h"

#include "helpers.h"
#include <iostream>

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

void BurnRitualObj(bool burnAll)
{
	// Devour:			SurvivalObjectBurnController
	// Molly:			SurvivalMollyAltarController
	// Inn:				InnMapController
	// Town:			SurvivalTownAltarController
	// Slaughterhouse:	SlaughterhouseAltarController

	/*  MAP: TOWN, DEVOUR
		DO_APP_FUNC(0x00562320, void, SurvivalObjectBurnController_BurnGoat, (SurvivalObjectBurnController * __this, MethodInfo * method));
		DO_APP_FUNC(0x00562590, void, SurvivalObjectBurnController_SkipToGoat, (SurvivalObjectBurnController * __this, int32_t number, MethodInfo * method));
	*/

	if (!IsHost()) {
		return;
	}

	Wrapper wrapper;
	const Il2CppImage* image = wrapper.GetImage("Assembly-CSharp.dll");

	std::string sceneName = get_SceneName();

	std::cout << "call..\n";

	// !!!!Check if Azazel is awake.
	BurnManager(sceneName, wrapper, image, burnAll);
}

void BurnManager(std::string& sceneName, Wrapper& wrapper, const Il2CppImage* image, bool burnAll)
{
	int32_t num = 10;

	if (sceneName == std::string("Devour")) {

		Il2CppObject* object = wrapper.GetObjectFromClass(image, "", "SurvivalObjectBurnController");

		if (object != nullptr) {
			auto SurvivalObjectBurnController_Object = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

			if (SurvivalObjectBurnController_Object) {
				auto SurvivalObjectBurnController = reinterpret_cast<app::SurvivalObjectBurnController*>(SurvivalObjectBurnController_Object);

				if (SurvivalObjectBurnController) {

					if (burnAll) {
						if (app::SurvivalObjectBurnController_SkipToGoat) {
							app::SurvivalObjectBurnController_SkipToGoat(SurvivalObjectBurnController, num, nullptr);
						}
					}
					else {
						if (app::SurvivalObjectBurnController_BurnGoat) {
							app::SurvivalObjectBurnController_BurnGoat(SurvivalObjectBurnController, nullptr);
						}
					}
				}
			}
		}
	}
	else if (sceneName == std::string("Molly")) {

		/*
		MAP: MOLLY
		DO_APP_FUNC(0x0055C100, void, SurvivalMollyAltarController_SkipToGoat, (SurvivalMollyAltarController * __this, int32_t number, MethodInfo * method));
		DO_APP_FUNC(0x0055C8E0, void, SurvivalMollyAltarController_OnGoat, (SurvivalMollyAltarController * __this, MethodInfo * method));
		*/

		Il2CppObject* object = wrapper.GetObjectFromClass(image, "", "SurvivalMollyAltarController");

		if (object != nullptr) {
			auto MollyAltarController_Object = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

			if (MollyAltarController_Object) {
				auto SurvivalMollyAltarController = reinterpret_cast<app::SurvivalMollyAltarController*>(MollyAltarController_Object);

				if (SurvivalMollyAltarController) {

					if (burnAll) {
						if (app::SurvivalMollyAltarController_SkipToGoat) {
							app::SurvivalMollyAltarController_SkipToGoat(SurvivalMollyAltarController, num, nullptr);
						}
					}
					else {
						if (app::SurvivalMollyAltarController_OnGoat) {
							app::SurvivalMollyAltarController_OnGoat(SurvivalMollyAltarController, nullptr);
						}
					}

				}
			}
		}
	}
	else if (sceneName == std::string("Inn")) {

		/*	MAP: INN
		DO_APP_FUNC(0x00930CD0, void, MapController_SetProgressTo, (MapController * __this, int32_t progress, MethodInfo * method));
		DO_APP_FUNC(0x00930EA0, void, MapController_IncreaseProgress, (MapController * __this, MethodInfo * method));
		*/

		Il2CppObject* object = wrapper.GetObjectFromClass(image, "", "SurvivalMollyAltarController");

		if (object != nullptr) {
			auto MapController_Object = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

			if (MapController_Object) {
				auto MapController = reinterpret_cast<app::MapController*>(MapController_Object);

				if (MapController) {

					if (burnAll) {
						if (app::MapController_SetProgressTo) {
							app::MapController_SetProgressTo(MapController, num, nullptr);
						}
					}
					else {
						if (app::MapController_IncreaseProgress) {
							app::MapController_IncreaseProgress(MapController, nullptr);
						}
					}
				}
			}
		}
	}
	else if (sceneName == std::string("Town")) {
		/*  MAP: TOWN, DEVOUR
		DO_APP_FUNC(0x00562320, void, SurvivalObjectBurnController_BurnGoat, (SurvivalObjectBurnController * __this, MethodInfo * method));
		DO_APP_FUNC(0x00562590, void, SurvivalObjectBurnController_SkipToGoat, (SurvivalObjectBurnController * __this, int32_t number, MethodInfo * method));
		*/

		Il2CppObject* object = wrapper.GetObjectFromClass(image, "", "SurvivalMollyAltarController");

		if (object != nullptr) {
			auto MapController_Object = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

			if (MapController_Object) {
				auto MapController = reinterpret_cast<app::MapController*>(MapController_Object);

				if (MapController) {

					if (burnAll) {
						if (app::MapController_SetProgressTo) {
							app::MapController_SetProgressTo(MapController, num, nullptr);
						}
					}
					else {
						if (app::MapController_IncreaseProgress) {
							app::MapController_IncreaseProgress(MapController, nullptr);
						}
					}
				}
			}
		}
	}
	else if (sceneName == std::string("Slaughterhouse")) {
		/* MAP: Slaughterhouse
		DO_APP_FUNC(0x0050DEB0, void, SlaughterhouseAltarController_SkipToGoat, (SlaughterhouseAltarController * __this, int32_t number, MethodInfo * method));
		*/

		Il2CppObject* object = wrapper.GetObjectFromClass(image, "", "SlaughterhouseAltarController");

		if (object != nullptr) {
			auto SlaughterhouseAltarController_Object = app::Object_1_FindObjectOfType(reinterpret_cast<app::Type*>(object), nullptr);

			if (SlaughterhouseAltarController_Object) {
				auto SlaughterhouseAltarController = reinterpret_cast<app::SlaughterhouseAltarController*>(SlaughterhouseAltarController_Object);

				if (SlaughterhouseAltarController) {

					if (burnAll) {
						if (app::SlaughterhouseAltarController_SkipToGoat) {
							app::SlaughterhouseAltarController_SkipToGoat(SlaughterhouseAltarController, num, nullptr);
						}
					}
					else {
						return;
					}
				}
			}
		}
	}
	else {
		return;
	}
}
