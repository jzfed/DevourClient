#pragma once

#include <string>

bool IsSinglePlayer();
bool IsOnline();
bool IsHost();
app::Menu* get_HorrorMenu();
std::string get_SceneName();