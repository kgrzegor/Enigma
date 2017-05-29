#include "Component.h"

bool Component::wrongInput(int letter) {
    return letter > ALPHA_SIZE || letter < 0;
}

void Component::normalizeInt(int &letter) {
    letter-=(int)'A';
}
