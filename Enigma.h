#ifndef ENIGMA_ENIGMA_H
#define ENIGMA_ENIGMA_H

#include <vector>

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

class Enigma{
    int nRotors;
    int letter;
    Plugboard *ptrPlugboard;
    Reflector *ptrReflector;
    std::vector<Rotor*> rotors;

    void rotateRotors();

    int charToInt(char c);

    char intToChar(int n);

    char encryptChar(char c);

    void encryptLetter(Component * ptr);

    bool validPbFile(const char *fileName);

    bool validRotorFiles (std::vector<const char *> rotorFiles);

    bool validRotSets (const char *rotSets, int nRotors);

public:
    Enigma(const char* pbFile, std::vector <const char*> rotorFiles, const char* rotSets);

    ~Enigma();

    void encryptFile(const char* inputFile, const char* outputFile);

};
#endif //ENIGMA_ENIGMA_H
