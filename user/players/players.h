#pragma once
#include <vector>

namespace Players {
	app::GameObject__Array* GetAllPlayers();
}

namespace Player {
	app::GameObject* GetLocalPlayer();
	app::NolanBehaviour* GetNolan();
}