#ifndef ENIGMA_PLUGBOARD_H
#define ENIGMA_PLUGBOARD_H

#include <map>

#include "Component.h"

class Plugboard : public Component
{
    ///przechowuje zmiany liter;
    std::map<int, int> plugboardSettings;

public:
    ///tworzy Plugboard na podstawie wczytanego pliku "pbs/*file*.pb"
    Plugboard(const char* fileName);

    ///szyfruje dana litere wg. plugboardSettings
    int encrypt(int letter);
};

#endif //ENIGMA_PLUGBOARD_H
