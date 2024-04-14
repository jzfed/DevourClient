#include "pch-il2cpp.h"

#include "misc.h"
#include "ClientHelper.h"

void Misc::SetRank(int rank)
{
	//
}

void Misc::SetSteamName(std::string& name)
{
	get_HorrorMenu()->fields.steamName = reinterpret_cast<app::String*>(il2cpp_string_new("0x"));
}

void Misc::ForceStart()
{
	if (IsHost()) {
		app::Menu_OnLobbyStartButtonClick(get_HorrorMenu(), nullptr);
	}
}
