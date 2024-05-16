#include "pch-il2cpp.h"

#include "players.h"

#include <iostream>


app::GameObject__Array* Players::GetAllPlayers()
{
	app::String* playerTagStr = reinterpret_cast<app::String*>(il2cpp_string_new("Player"));

	if (app::GameObject_FindGameObjectsWithTag) {
		app::GameObject__Array* playersTag = app::GameObject_FindGameObjectsWithTag(playerTagStr, nullptr);

		if (playersTag) {
			return playersTag;
		}
	}

	return nullptr;
}

app::GameObject* Player::GetLocalPlayer()
{
	app::GameObject__Array* playerList = Players::GetAllPlayers();
	app::String* NolanBehaviourStr = reinterpret_cast<app::String*>(il2cpp_string_new("NolanBehaviour"));

	if (!playerList || playerList->max_length == 0)
		return nullptr;

	il2cpp_array_size_t _size = playerList->max_length;
	for (int i = 0; i < _size; i++) {
		app::GameObject* currentPlayer = playerList->vector[i];

		if (app::GameObject_GetComponentByName) {
			app::Component* nbComponent = app::GameObject_GetComponentByName(currentPlayer, NolanBehaviourStr, nullptr);

			if (nbComponent) {
				app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);

				if (nb) {

					if (app::BoltEntity_get_IsOwner != nullptr && currentPlayer != nullptr) {

						app::BoltEntity* entity = nb->fields._._._._._entity;

						if (entity) {
							if (app::BoltEntity_get_IsOwner(entity, nullptr)) {
								return currentPlayer;
							}
						}

					}
				}
			}
		}
	}
	return nullptr;
}

app::NolanBehaviour* Player::GetNolan()
{
	app::GameObject* localPlayer = Player::GetLocalPlayer();
	app::String* NolanBehaviourStr = reinterpret_cast<app::String*>(il2cpp_string_new("NolanBehaviour"));

	if (localPlayer) {
		if (app::GameObject_GetComponentByName) {
			app::Component* nbComponent = app::GameObject_GetComponentByName(localPlayer, NolanBehaviourStr, nullptr);

			if (nbComponent) {
				app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);

				if (nb) {
					return nb;
				}
			}
		}
	}

	return nullptr;
}


