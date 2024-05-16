#pragma once

#include "settings/settings.hpp"

#include <iostream>

namespace Misc {
    void ForceStart();
    void CarryItem(const char* itemName);
    void CarryAnimal(const char* animalName);
    void InstantWin();
    void CustomizedLobby();
    void FullBright();
    void Fly();
    void Revive(bool self);
    void GetKeys();
    void Jumpscare();
    void Kill(bool self);
    void RankSpoofer(int value);
}