#pragma once

#include <string>

class Wrapper;

bool IsSinglePlayer();
bool IsOnline();
bool IsHost();

app::Menu* get_HorrorMenu();
std::string get_SceneName();

void BurnRitualObj(bool burnAll);
void BurnManager(std::string& sceneName, Wrapper& wrapper, const Il2CppImage* image, bool burnAll);