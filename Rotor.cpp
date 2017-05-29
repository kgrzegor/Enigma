#include <stdexcept>
#include <fstream>
#include <iostream>

#include "Rotor.h"

using  namespace std;

Rotor::Rotor(const char *fileName, int rotSet) {
    int set, i=0;
    int letterEncrypted[ALPHA_SIZE]={};
    nRotation = rotSet;

    fstream settings;
    settings.open(fileName, fstream::in);

    if(!settings)
        throw runtime_error("Error rotor: can't open .rot file");

    while (settings >> set) /// mozna by to zmienic na litery zamiast liczb w pliku;
    {
        cout << set;
        normalizeInt(set);
        if(wrongInput(set))
            throw runtime_error("Error rotor file: wrong character");

        forwardSet[i]=set-i;
        if (forwardSet[i]<0)
            forwardSet[i]+=ALPHA_SIZE;

        backwardSet[set]=i-set;
        if (backwardSet[set]<0)
            backwardSet[set]+=ALPHA_SIZE;

        letterEncrypted[set]++;
        i++;
    }
    settings.close();

      if (i!=ALPHA_SIZE)
          throw runtime_error("Error rotor file: wrong number of characters");

      for (i = 0; i < ALPHA_SIZE; ++i) {
          if (letterEncrypted[i] == 0)
              throw runtime_error("Error rotor file: character not encrypted");
          if (letterEncrypted[i] > 1)
              throw runtime_error("Error rotor file: character encrypted more than once");
      }
}

bool Rotor::isFullyRotated() {
    return nRotation==ALPHA_SIZE;
}

void Rotor::rotate() {
    if (isFullyRotated())
        throw runtime_error("Error rotor: rotor is fully rotated!");
    nRotation++;
}

int Rotor::encrypt(int letter) {
    return (letter+forwardSet[(nRotation+letter)%ALPHA_SIZE])%ALPHA_SIZE;
}

int Rotor::encryptBackward(int letter) {
    return (letter+backwardSet[(nRotation+letter)%ALPHA_SIZE])%ALPHA_SIZE;
}

void Rotor::resetRotor() {
    nRotation=0;
}
