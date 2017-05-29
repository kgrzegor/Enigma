#include <fstream>
#include <stdexcept>
#include "Plugboard.h"

using namespace std;

Plugboard::Plugboard(const char *fileName) {
    int inputLetter, outputLetter;
    int letterEncypted[ALPHA_SIZE]={};
    fstream settings;
    settings.open(fileName, fstream::in);

    if (!settings)
        throw runtime_error("Error plugboard: can't open .pb file");

    while (settings >> inputLetter) {
        if (settings >> outputLetter) {
            normalizeInt(inputLetter);
            normalizeInt(outputLetter);
            if (wrongInput(inputLetter) || wrongInput(outputLetter))
                throw runtime_error("Error plugboard file: wrong character");
            else {
                plugboardSettings[inputLetter] = outputLetter;
            }
        } else
            throw runtime_error("Error plugboard file: odd number of pairs");
    }
    settings.close();
    map<int, int>::iterator it = plugboardSettings.begin();
    while (it != plugboardSettings.end())
    {
        letterEncypted[it->first]++;
        letterEncypted[it->second]++;
        it++;
    }
    for (int i = 0; i < ALPHA_SIZE; ++i) {
        if (letterEncypted[i]>1)
            throw runtime_error("Error plugboard file: letter encypted more than once");
    }

}

int Plugboard::encrypt(int letter) {
    if (wrongInput(letter))
        throw runtime_error("Error plugboard: wrong input");

    map<int, int>::iterator it = plugboardSettings.begin();
    while (it != plugboardSettings.end()) {
        if (it->first == letter)
            return it->second;
        else if (it->second == letter)
            return it->first;
        it++;
    }
    return letter;
}


