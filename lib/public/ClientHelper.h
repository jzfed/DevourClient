#pragma once


bool IsSinglePlayer();
bool IsOnline();
bool IsHost();
app::Survival* GetSurvivalObject();
app::OptionsHelpers* GetOptionsHelpersObject();
bool IsLocalPlayer(app::NolanBehaviour* player);
bool IsPlayerCrawling();
bool IsPlayerCrawling(app::GameObject* go);
bool IsInGame();
bool IsSequencePlaying();
app::GameObject* GetAzazel(app::Survival* survival);
std::string SceneName();
std::string GetAzazelName();
float Time_DeltaTime();