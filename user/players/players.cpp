#include "pch-il2cpp.h"

#include "players.h"

#include <iostream>
#include "ClientHelper.h"


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
	static app::GameObject* cachedLocalPlayer = nullptr;

	if (cachedLocalPlayer != nullptr) {
		// Check if cached player is still valid
		if (IsNull((app::Object_1*)cachedLocalPlayer)) {
			cachedLocalPlayer = nullptr;
		}
		else {
			return cachedLocalPlayer;
		}
	}

	app::GameObject__Array* playerList = Players::GetAllPlayers();
	app::String* NolanBehaviourStr = reinterpret_cast<app::String*>(il2cpp_string_new("NolanBehaviour"));

	if (!playerList || playerList->max_length == 0)
		return nullptr;

	il2cpp_array_size_t _size = playerList->max_length;
	for (int i = 0; i < _size; i++) {
		app::GameObject* currentPlayer = playerList->vector[i];

		if (IsNull((app::Object_1*)currentPlayer)) {
			continue;
		}
		else {
			if (app::GameObject_GetComponentByName) {
				app::Component* nbComponent = app::GameObject_GetComponentByName(currentPlayer, NolanBehaviourStr, nullptr);

				if (nbComponent) {
					app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);

					if (nb && IsLocalPlayer(nb)) {
						cachedLocalPlayer = currentPlayer;
						return currentPlayer;
					}
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
		app::String* NolanBehaviourStr = reinterpret_cast<app::String*>(il2cpp_string_new("NolanBehaviour"));
		if (app::GameObject_GetComponentByName) {
			app::Component* nbComponent = app::GameObject_GetComponentByName(localPlayer, NolanBehaviourStr, nullptr);

			if (nbComponent) {
				app::NolanBehaviour* nb = reinterpret_cast<app::NolanBehaviour*>(nbComponent);
				if (nb) {
					cachedNolan = nb;
					lastLocalPlayer = localPlayer;
				}
			}
		}
	}

	return cachedNolan;
}


