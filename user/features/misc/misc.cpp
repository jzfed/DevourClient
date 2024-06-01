#include "pch-il2cpp.h"

#include "Misc.h"
#include "Wrapper.h"
#include "ClientHelper.h"
#include "players/players.h"
#include "helpers.h"
#include "UnityCore.h"
#include <iostream>
#include "Windows.h"
#include <map>

void Misc::ForceStart()
{
	std::string _scene = SceneName();

	if (IsHost() && _scene == std::string("Menu")) {
		app::Menu* _menu = UnityCore::Object<app::Menu>::FindObjectOfType("Menu", "Horror");

		if (_menu) {
			if (app::Menu_OnLobbyStartButtonClick) {
				app::Menu_OnLobbyStartButtonClick(_menu, nullptr);
			}
		}
	}
}

void Misc::CarryItem(const char* itemName)
{
	std::string _scene = SceneName();

	if (_scene == std::string("Menu")) {
		return;
	}

	std::map<std::string, std::string> itemMap = {
		{"Hay", "SurvivalHay"},
		{"First aid", "SurvivalFirstAid"},
		{"Bone", "SurvivalBone"},
		{"Battery", "SurvivalBattery"},
		{"Gasoline", "SurvivalGasoline"},
		{"Fuse", "SurvivalFuse"},
		{"Food", "SurvivalRottenFood"},
		{"Bleach", "SurvivalBleach"},
		{"Ritual Book (inactive)", "RitualBook-InActive-1"},
		{"Ritual Book (active)", "RitualBook-Active-1"},
		{"Matchbox", "Matchbox-3"},
		{"Egg 1", "Egg-Clean-1"},
		{"Egg 2", "Egg-Clean-2"},
		{"Egg 3", "Egg-Clean-3"},
		{"Egg 4", "Egg-Clean-4"},
		{"Egg 5", "Egg-Clean-5"},
		{"Egg 6", "Egg-Clean-6"},
		{"Egg 7", "Egg-Clean-7"},
		{"Egg 8", "Egg-Clean-8"},
		{"Egg 9", "Egg-Clean-9"},
		{"Egg 10", "Egg-Clean-10"}
	};

	std::string carryItem = itemMap[itemName];

	if (!carryItem.empty() && Player::GetLocalPlayer()) {
		app::String* str2 = reinterpret_cast<app::String*>(il2cpp_string_new(carryItem.c_str()));
		app::NolanBehaviour_StartCarry(Player::GetNolan(), str2, nullptr);
	}
}

void Misc::CarryAnimal(const char* animalName)
{
	std::string _scene = SceneName();

	if (_scene == std::string("Menu")) {
		return;
	}

	std::map<std::string, std::string> animalMap = {
		{"Rat", "SurvivalRat"},
		{"Goat", "SurvivalGoat"},
		{"Pig", "SurvivalPig"}
	};

	std::string carryAnimal = animalMap[animalName];

	if (!carryAnimal.empty() && Player::GetLocalPlayer()) {
		app::String* str2 = reinterpret_cast<app::String*>(il2cpp_string_new(carryAnimal.c_str()));
		app::NolanBehaviour_StartCarry(Player::GetNolan(), str2, nullptr);
	}
}

void Misc::InstantWin()
{
	// app::InnMapController -> Inn
	// app::SlaughterhouseAltarController -> Slaughterhouse
	// SurvivalObjectBurnController -> other

	std::string _scene = SceneName();

	if (_scene == std::string("Menu") && !IsHost() && !Player::GetLocalPlayer()) {
		return;
	}

	int32_t progress = 10;

	if (_scene == std::string("Inn")) {
		app::MapController* _MapController = UnityCore::Object<app::MapController>::FindObjectOfType("MapController");

		if (_MapController) {

			// DO_APP_FUNC(0x00930CD0, void, MapController_SetProgressTo, (MapController * __this, int32_t progress, MethodInfo * method));

			if (app::MapController_SetProgressTo != nullptr) {
				app::MapController_SetProgressTo(_MapController, progress, nullptr);
			}
		}
	}
	else if (_scene == std::string("Slaughterhouse")) {
		app::SlaughterhouseAltarController* _SlaughterhouseAltarController = UnityCore::Object<app::SlaughterhouseAltarController>::FindObjectOfType("SlaughterhouseAltarController");

		if (_SlaughterhouseAltarController) {

			// DO_APP_FUNC(0x0050DEB0, void, SlaughterhouseAltarController_SkipToGoat, (SlaughterhouseAltarController * __this, int32_t number, MethodInfo * method));

			if (app::SlaughterhouseAltarController_SkipToGoat != nullptr) {
				app::SlaughterhouseAltarController_SkipToGoat(_SlaughterhouseAltarController, progress, nullptr);
			}
		}
	}
	else {
		app::SurvivalObjectBurnController* _SurvivalObjectBurnController = UnityCore::Object<app::SurvivalObjectBurnController>::FindObjectOfType("SurvivalObjectBurnController");

		if (_SurvivalObjectBurnController) {
			// DO_APP_FUNC(0x00562590, void, SurvivalObjectBurnController_SkipToGoat, (SurvivalObjectBurnController * __this, int32_t number, MethodInfo * method));

			if (app::SurvivalObjectBurnController_SkipToGoat != nullptr) {
				app::SurvivalObjectBurnController_SkipToGoat(_SurvivalObjectBurnController, progress, nullptr);
			}
		}
	}
}

void Misc::CustomizedLobby()
{

}

// This function has not been tested
void Misc::SpawnPrefab(const char* prefabName) {

	if (IsHost() == false) { return; }

	std::string _scene = SceneName();
	if (_scene == std::string("Menu")) return;

	if (il2cppi_is_initialized(app::BoltPrefabs__TypeInfo)) {

		app::BoltPrefabs__StaticFields* _prefab_field = (*app::BoltPrefabs__TypeInfo)->static_fields;


		std::map<const char*, app::PrefabId> prefabMapDevour = {
		{"TV", _prefab_field->TV},
		{"Devour Door Back", _prefab_field->DevourDoorBack},
		{"Devour Door Main", _prefab_field->DevourDoorMain},
		{"Devour Door Room", _prefab_field->DevourDoorRoom},
		{"Animal Gate", _prefab_field->Animal_Gate},
		{"DoorNumber", _prefab_field->DoorNumber},
		{"Town Door", _prefab_field->TownDoor},
		{"Inn Double Door", _prefab_field->InnDoubleDoor},
		{"Slaughterhouse Fire Escape Door", _prefab_field->SlaughterhouseFireEscapeDoor},
		{"Asylum White Door", _prefab_field->AsylumWhiteDoor},
		{"Town Cell Door", _prefab_field->TownCellDoor},
		};

		app::PrefabId p = prefabMapDevour[prefabName];

		app::GameObject* localPlayer = Player::GetLocalPlayer();
		if (localPlayer) {
			app::Quaternion rotation = app::Quaternion_get_identity(NULL);

			app::Transform* playerTransform = Unity::Transform::Get(localPlayer);
			if (playerTransform == nullptr) return;

			app::Vector3 playerPos = Unity::Transform::Position(playerTransform);

			if (app::BoltNetwork_Instantiate_6) {
				app::GameObject* go = (app::GameObject*)app::BoltNetwork_Instantiate_6(p, playerPos, rotation, nullptr);
			}
		}
	}
}

void Misc::RankSpoofer(int value) {

	app::GameObject* player = Player::GetLocalPlayer();

	if (player == nullptr) {
		return;
	}
	else {
		app::NolanRankController* rankController = UnityCore::Object<app::NolanRankController>::FindObjectOfType("NolanRankController");

		if (rankController != nullptr) {
			if (app::NolanRankController_SetRank != nullptr) {
				app::NolanRankController_SetRank(rankController, value, nullptr);
			}
		}
	}
}

void Misc::FullBright(app::NolanBehaviour* nb)
{
	if (nb != nullptr) {
		app::Light* _flashlight = nb->fields.flashlightSpot;

		app::Light_set_intensity(_flashlight, 0.8f, nullptr);
		app::Light_set_range(_flashlight, 700.0f, nullptr);
		app::Light_set_spotAngle(_flashlight, 179.0f, nullptr);

		app::Light_set_shadows(_flashlight, app::LightShadows__Enum::None, nullptr);
	}
}


void Misc::Revive(bool self)
{
	std::string _scene = SceneName();

	if (_scene == std::string("Menu")) {
		return;
	}

	// app::SurvivalReviveInteractable
	app::SurvivalReviveInteractable* revive = UnityCore::Object<app::SurvivalReviveInteractable>::FindObjectOfType("SurvivalReviveInteractable");

	if (revive == NULL) {
		if (self) {
			app::GameObject* localPlayer = Player::GetLocalPlayer();

			if (IsPlayerCrawling() && localPlayer != NULL) {
				app::NolanBehaviour* nb = Player::GetNolan();
				if (nb != NULL) {
					app::Vector3 vec{ 0.f, -100.f, 0.f };

					if (app::Quaternion_get_identity != nullptr && app::NolanBehaviour_TeleportTo != nullptr) {
						app::NolanBehaviour_TeleportTo(nb, vec, app::Quaternion_get_identity(nullptr), false, nullptr);
					}
				}
			}
		}
	}
	else {
		if (self) {
			app::GameObject* localPlayer = Player::GetLocalPlayer();

			if (localPlayer != NULL) {
				if (IsPlayerCrawling()) {
					app::SurvivalReviveInteractable_Interact(revive, localPlayer, nullptr);
				}
			}
		}
		else {
			app::GameObject__Array* players = Players::GetAllPlayers();

			if (players != NULL) {
				for (int i = 0; i < players->max_length; i++) {
					app::GameObject* currentGo = players->vector[i];

					if (currentGo) {
						if (IsPlayerCrawling(currentGo)) {
							app::SurvivalReviveInteractable_Interact(revive, currentGo, nullptr);
						}
					}
				}
			}
		}
	}
}

void Misc::GetKeys() {

}

void Misc::Jumpscare() {
	std::string _scene = SceneName();

	if (_scene == std::string("Menu")) {
		return;
	}

	if (IsHost() == false) {
		return;
	}

	app::Survival* survival = UnityCore::Object<app::Survival>::FindObjectOfType("Survival");
	if (survival == NULL) { return; }

	app::SurvivalAzazelBehaviour* azazel = UnityCore::Object<app::SurvivalAzazelBehaviour>::FindObjectOfType("SurvivalAzazelBehaviour");

	app::GameObject* ai = GetAzazel(survival);

	if (azazel != NULL) {

		app::GameObject__Array* players = Players::GetAllPlayers();
		if (players == NULL) { return; }

		for (int i = 0; i < players->max_length; i++) {
			app::GameObject* currentPlayer = players->vector[i];

			if (currentPlayer == NULL) continue;

			app::Component* component = Unity::GameObject::GetComponentByName(currentPlayer, "NolanBehaviour");

			if (component != NULL) {
				app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(component);

				if (nb != NULL) {
					if (!IsLocalPlayer(nb)) {
						if (app::SurvivalAzazelBehaviour_OnPickedUpPlayer != nullptr) {
							app::SurvivalAzazelBehaviour_OnPickedUpPlayer(azazel, ai, currentPlayer, true, nullptr);
						}
					}
				}
			}
		}
	}
}

void Misc::Kill(bool self) {
	std::string _scene = SceneName();

	if (_scene == std::string("Menu")) {
		return;
	}

	if (IsHost() == false) {
		return;
	}

	app::Survival* survival = UnityCore::Object<app::Survival>::FindObjectOfType("Survival");
	if (survival == NULL) { return; }

	app::SurvivalAzazelBehaviour* azazel = UnityCore::Object<app::SurvivalAzazelBehaviour>::FindObjectOfType("SurvivalAzazelBehaviour");

	app::GameObject* ai = GetAzazel(survival);

	if (azazel != NULL) {

		if (self) {
			app::GameObject* localPlayer = Player::GetLocalPlayer();

			if (localPlayer == NULL) return;

			//DO_APP_FUNC(0x00622990, void, SurvivalAzazelBehaviour_OnKnockout, (SurvivalAzazelBehaviour * __this, GameObject * ai, GameObject * player, MethodInfo * method));
			if (app::SurvivalAzazelBehaviour_OnKnockout != nullptr) {
				app::SurvivalAzazelBehaviour_OnKnockout(azazel, ai, localPlayer, nullptr);
			}
		}
		else {
			app::GameObject__Array* players = Players::GetAllPlayers();
			if (players == NULL) { return; }

			for (int i = 0; i < players->max_length; i++) {
				app::GameObject* currentPlayer = players->vector[i];

				if (currentPlayer == NULL) continue;

				app::Component* component = Unity::GameObject::GetComponentByName(currentPlayer, "NolanBehaviour");

				if (component != NULL) {
					app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(component);

					if (nb != NULL) {

						if (IsLocalPlayer(nb) && !self)
							continue;

						//DO_APP_FUNC(0x00622990, void, SurvivalAzazelBehaviour_OnKnockout, (SurvivalAzazelBehaviour * __this, GameObject * ai, GameObject * player, MethodInfo * method));
						if (app::SurvivalAzazelBehaviour_OnKnockout != nullptr) {
							app::SurvivalAzazelBehaviour_OnKnockout(azazel, ai, currentPlayer, nullptr);
						}
					}
				}
			}
		}
	}
}

void Misc::TpToAzazel()
{
	std::string _scene = SceneName();

	if (_scene == std::string("Menu")) return;

	app::GameObject* go = Player::GetLocalPlayer();

	if (go) {
		app::NolanBehaviour* nb = Player::GetNolan();

		if (nb == nullptr) return;

		app::Survival* _survival = UnityCore::Object<app::Survival>::FindObjectOfType("Survival");
		if (_survival == nullptr) return;

		// get azazel
		app::GameObject* azazelGo = GetAzazel(_survival);
		if (azazelGo == nullptr) return;

		// get transform of azazel
		app::Transform* transform = app::GameObject_get_transform(azazelGo, nullptr);
		if (transform == nullptr) return;

		app::Vector3 v3 = app::Transform_get_position(transform, nullptr);
		app::Quaternion rotation = app::Quaternion_get_identity(nullptr);

		if (app::NolanBehaviour_TeleportTo != nullptr) {
			app::NolanBehaviour_TeleportTo(nb, v3, rotation, false, nullptr);
		}
	}
}

void Misc::UnlockAchievements()
{
	app::AchievementHelpers* achievementsSingleton = app::AchievementHelpers_get_singleton(nullptr);

	if (achievementsSingleton != nullptr) {

		const char* achievements[] = {
			"ACH_ALL_CLIPBOARDS_READ", "ACH_ALL_NOTES_READ", "ACH_UNLOCKED_CAGE",
			"ACH_UNLOCKED_ATTIC_CAGE", "ACH_CALMED_ANNA", "ACH_FRIED_RAT",
			"ACH_BURNT_GOAT", "ACH_KNOCKED_OUT_BY_ANNA", "ACH_KNOCKOUT_OUT_BY_DEMON",
			"ACH_KNOCKED_OUT_IN_HIDING", "STAT_NUM_BLEACH_USED", "ACH_WON_SP",
			"ACH_WIN_NIGHTMARE", "ACH_WON_HARD_SP", "ACH_WON_COOP", "ACH_WON_HARD",
			"ACH_WIN_NIGHTMARE_SP", "ACH_LOST", "ACH_NEVER_KNOCKED_OUT",
			"ACH_ONLY_ONE_KNOCKED_OUT", "ACH_WON_HARD_NO_MEDKITS", "ACH_WON_NO_MEDKITS",
			"ACH_WON_NO_BATTERIES", "ACH_WON_NIGHTMARE_NO_MEDKITS",
			"ACH_WON_NO_KNOCKOUT_COOP", "ACH_WON_HARD_NO_BATTERIES",
			"ACH_WON_HARD_{0}", "ACH_WON_NIGHTMARE_{0}", "ACH_WON_NIGHTMARE_NO_BATTERIES",
			"ACH_SURVIVED_TO_7_GOATS", "ACH_SURVIVED_TO_5_GOATS", "ACH_SURVIVED_TO_3_GOATS",
			"ACH_WON_Manor_NIGHTMARE_SP", "ACH_WON_NIGHTMARE_", "ACH_WON_MANOR_NIGHTMARE_SP",
			"ACH_WON_TOWN_HARD", "ACH_WON_INN_HARD_SP", "ACH_ALL_FEATHERS",
			"ACH_WON_SLAUGHTERHOUSE_COOP", "ACH_ALL_BARBED_WIRES", "ACH_WON_INN_HARD",
			"ACH_WON_MOLLY_HARD", "ACH_ALL_HORSESHOES", "ACH_WON_MOLLY_HARD_SP",
			"ACH_WON_TOWN_NIGHTMARE_SP", "ACH_100_GASOLINE_USED", "ACH_WON_INN_SP",
			"ACH_WON_MANOR_HARD_SP", "ACH_WON_MOLLY_SP", "ACH_1000_PIGS_DESTROYED",
			"ACH_1000_MIRRORS_DESTROYED", "ACH_100_EGGS_DESTROYED", "ACH_WON_SLAUGHTERHOUSE_HARD_SP",
			"ACH_WON_TOWN_COOP", "ACH_100_FUSES_USED", "ACH_WON_MOLLY_COOP",
			"ACH_WON_MOLLY_NIGHTMARE_SP", "ACH_1000_BOOKS_DESTROYED", "ACH_ALL_PATCHES",
			"ACH_WON_SLAUGHTERHOUSE_SP", "ACH_WON_TOWN_NIGHTMARE", "ACH_WON_INN_COOP",
			"ACH_ALL_CHERRY_BLOSSOM", "ACH_WON_TOWN_HARD_SP", "ACH_WON_MOLLY_NIGHTMARE",
			"ACH_WON_INN_NIGHTMARE_SP", "ACH_ALL_ROSES", "ACH_WON_TOWN_SP",
			"ACH_WON_SLAUGHTERHOUSE_NIGHTMARE_SP", "ACH_WON_INN_NIGHTMARE",
			"ACH_WON_MANOR_COOP", "ACH_WON_SLAUGHTERHOUSE_HARD", "ACH_WON_SLAUGHTERHOUSE_NIGHTMARE",
			"ACH_WON_MANOR_HARD", "ACH_WON_MANOR_NIGHTMARE", "ACH_WON_MANOR_SP"
		};


		int size = sizeof(achievements) / sizeof(achievements[0]);

		std::cout << "Achievements length: " << size << "\n";

		for (int i = 0; i < size; ++i) {
			app::String* currentachievements = reinterpret_cast<app::String*>(il2cpp_string_new(achievements[i]));

			// crash
			app::AchievementHelpers_Unlock(achievementsSingleton, currentachievements, false, nullptr);
		}
	}
}
