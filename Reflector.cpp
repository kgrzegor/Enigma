#include <stdexcept>

#include "reflector.h"

using namespace std;

int Reflector::encrypt(int letter) {
    if (wrongInput(letter))
        throw runtime_error("Error reflector: wrong input");
    return (letter+13)%26;
}
