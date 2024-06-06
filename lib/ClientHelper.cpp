#include "pch-il2cpp.h"

#include <helpers.h>

#include "ClientHelper.h"
#include "players/players.h"
#include "UnityEngine.h"

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
	if (go == NULL)
		return false;

	if (app::GameObject_GetComponentByName != NULL) {
		app::Component* nbComponent = app::GameObject_GetComponentByName(go, ConvertToSystemString("NolanBehaviour"), nullptr);

		if (nbComponent) {
			app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);

			if (nb) {
				return app::NolanBehaviour_IsCrawling(nb, nullptr);
			}
		}
	}

	return app::NolanBehaviour_IsCrawling(Player::GetNolan(), nullptr);
}

bool IsInGame()
{
	app::OptionsHelpers* optionsHelpers = UnityEngine::Object::FindObjectOfType<app::OptionsHelpers>("OptionsHelpers");

	if (optionsHelpers)
		return optionsHelpers->fields._inGame_k__BackingField;

	return false;
}

bool IsNull(app::Object_1* obj)
{
	if (obj == nullptr)
		return true;

	return !app::Object_1_op_Implicit(obj, nullptr);
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
