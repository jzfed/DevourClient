#include "pch-il2cpp.h"

#include <helpers.h>

#include "ClientHelper.h"
#include "players/players.h"
#include "UnityEngine/Engine.hpp"

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

bool IsLocalPlayer(app::NolanBehaviour* player)
{
	auto boltEntity = app::EntityBehaviour_get_entity((app::EntityBehaviour*)player, NULL);

	if (not boltEntity
		|| not app::BoltEntity_get_IsAttached(boltEntity, NULL)
		|| not app::BoltEntity_get_IsOwner(boltEntity, NULL))
		return false;

	return true;
}

bool IsPlayerCrawling()
{
	if (!Player::GetLocalPlayer())
		return false;

	return app::NolanBehaviour_IsCrawling(Player::GetNolan(), nullptr);
}

bool IsPlayerCrawling(app::GameObject* go)
{
	if (go == nullptr) return false;

	app::Component* nbComponent = GameObject::GetComponentByName(go, "NolanBehaviour");

	if (nbComponent) return false;

	app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);

	if (nb)
		return app::NolanBehaviour_IsCrawling(nb, nullptr);
	else
		return false;
}

bool IsInGame()
{
	app::OptionsHelpers* optionsHelpers = Object::FindObjectOfType<app::OptionsHelpers>("OptionsHelpers");

	if (optionsHelpers)
		return optionsHelpers->fields._inGame_k__BackingField;

	return false;
}

app::GameObject* GetAzazel(app::Survival* survival)
{
	app::GameObject* ai = app::Survival_GetAzazel(survival, nullptr);

	if (ai) {
		return ai;
	}

	return NULL;
}


std::string SceneName()
{
	if (app::SaveHelpers_get_singleton != nullptr) {
		app::SaveHelpers* SaveHelper = app::SaveHelpers_get_singleton(nullptr);

		if (SaveHelper) {

			std::string str = il2cppi_to_string(SaveHelper->fields.sceneName);

			return str;
		}
	}

	return std::string("");
}


float Time_DeltaTime()
{
	if (app::Time_1_get_deltaTime) {
		return app::Time_1_get_deltaTime(nullptr);
	}

	return 0.0f;
}
