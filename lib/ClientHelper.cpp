#include "pch-il2cpp.h"

#include "ClientHelper.h"

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

