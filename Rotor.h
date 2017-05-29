#ifndef ENIGMA_ROTOR_H
#define ENIGMA_ROTOR_H

#include "Component.h"

class Rotor : public Component
{
    int forwardSet[ALPHA_SIZE];

    int backwardSet[ALPHA_SIZE];

    int nRotation;

public:
    Rotor(const char* fileName, int rotSet);

    int encrypt(int letter);
    int encryptBackward(int letter);
    bool isFullyRotated();
    void rotate();
    void resetRotor();
};

#endif //ENIGMA_ROTOR_H
