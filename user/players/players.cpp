#include "pch-il2cpp.h"

#include "players.h"
#include <helpers.h>
#include "UnityEngine/Engine.hpp"
#include "ClientHelper.h"

app::GameObject__Array* Players::GetAllPlayers()
{
	app::GameObject__Array* players = Object::FindGameObjectsWithTag("Player");

	return players ? players : nullptr;
}

app::GameObject* Player::GetLocalPlayer()
{
	static app::GameObject* cachedLocalPlayer = nullptr;

	if (cachedLocalPlayer != nullptr) {
		// Check if cached player is still valid
		if (Object::IsNull((app::Object_1*)cachedLocalPlayer)) {
			cachedLocalPlayer = nullptr;
		}
		else {
			return cachedLocalPlayer;
		}
	}

	app::GameObject__Array* playerList = Players::GetAllPlayers();

	if (!playerList || playerList->max_length == 0)
		return nullptr;

	il2cpp_array_size_t _size = playerList->max_length;
	for (int i = 0; i < _size; i++) {
		app::GameObject* currentPlayer = playerList->vector[i];

		if (Object::IsNull((app::Object_1*)currentPlayer)) {
			continue;
		}
		else {
			app::Component* nbComponent = GameObject::GetComponentByName(currentPlayer, "NolanBehaviour");

			if (nbComponent) {
				app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);

				if (nb && IsLocalPlayer(nb)) {
					cachedLocalPlayer = currentPlayer;
					return currentPlayer;
				}
			}
		}
	}
	return nullptr;
}

app::NolanBehaviour* Player::GetNolan()
{
	static app::NolanBehaviour* cachedNolan = nullptr;
	static app::GameObject* lastLocalPlayer = nullptr;

	app::GameObject* localPlayer = Player::GetLocalPlayer();
	if (localPlayer == nullptr) return nullptr;

	if (lastLocalPlayer != localPlayer) {

		app::Component* nbComponent = GameObject::GetComponentByName(localPlayer, "NolanBehaviour");

		if (nbComponent) {

			app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);

			if (nb) {
				cachedNolan = nb;
				lastLocalPlayer = localPlayer;
			}
		}
	}

	return cachedNolan;
}


