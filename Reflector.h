#ifndef ENIGMA_REFLECTOR_H
#define ENIGMA_REFLECTOR_H

#include "Component.h"

class Reflector : public Component
{

public:

    int encrypt(int letter);
};


#endif //ENIGMA_REFLECTOR_H
