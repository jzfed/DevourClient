#pragma once


bool IsSinglePlayer();
bool IsOnline();
bool IsHost();
bool IsLocalPlayer(app::NolanBehaviour* player);
bool IsPlayerCrawling();
bool IsPlayerCrawling(app::GameObject* go);
bool IsInGame();
bool IsNull(app::Object_1* obj);

app::GameObject* GetAzazel(app::Survival* survival);

std::string SceneName();
float Time_DeltaTime();