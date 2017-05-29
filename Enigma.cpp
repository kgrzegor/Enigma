#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

#include "Enigma.h"

using namespace std;

Enigma::Enigma(const char *pbFile, vector<const char *> rotorFiles, const char* rotSets) {

    if(!validPbFile(pbFile))
        throw runtime_error("Error: Invalid .pb file");
    if(!validRotorFiles(rotorFiles))
        throw runtime_error("Error: Invalid .rot files");
    if(!validRotSets(rotSets, rotorFiles.size()))
        throw runtime_error("Error: Invalid rotors' starting positions");

    nRotors = rotorFiles.size();

    ptrPlugboard = new Plugboard(pbFile);

    ptrReflector = new Reflector();

    for (int i = 0; i < nRotors; ++i)
        rotors.push_back(new Rotor(rotorFiles[i],charToInt(rotSets[i])));
}

Enigma::~Enigma() {
    delete ptrPlugboard;
    delete ptrReflector;
    for (int i = 0; i < nRotors; ++i)
        delete rotors[i];
}

void Enigma::rotateRotors() {
    rotors[0]->rotate();

    for (int i = 0; i < nRotors-1; ++i) {
        if(rotors[i]->isFullyRotated()){
            rotors[i]->resetRotor();
            rotors[i+1]->rotate();
        }
    }

    if (rotors[nRotors-1]->isFullyRotated())
        rotors[nRotors-1]->resetRotor();
}

int Enigma::charToInt(char c) {
    if (isupper(c)) return c - 'A';
    else return c - 'a';
}

char Enigma::intToChar(int n) {
    return (char)(n + 'a');
}

char Enigma::encryptChar(char c) {
    if (!isalpha(c))
        return c; //innych znakow niz litery nie zmieniamy

    bool upperLetter = isupper(c); //pamietamy czy litera byla wielka

    letter = charToInt(c);

    encryptLetter(ptrPlugboard); //przejscie przez plugboard

    for (int i = 0; i < nRotors; ++i)
    {
        encryptLetter(rotors[i]);//przejscie przez wszystkie rotory
    }

    encryptLetter(ptrReflector);//przejscie przez reflector

    for (int i = nRotors-1; i >= 0; --i)
        letter = rotors[i]->encryptBackward(letter);//powrot przez wszystkie rotory

    encryptLetter(ptrPlugboard);//przejscie ponownie przez plugboard

    c = intToChar(letter);
    rotateRotors();
    if (upperLetter)
        return toupper(c);
    else
        return c;
}

void Enigma::encryptLetter(Component *ptr) {
    letter = ptr->encrypt(letter);
}

void Enigma::encryptFile(const char *inputFile, const char *outputFile) {
    string plainLine,encryptedLine;
    fstream input,output;

    input.open(inputFile,fstream::in);
    if(!input)
        throw runtime_error("Error enigma: can't open file to encrypt/decrypt");

    output.open(outputFile, fstream::out | fstream::trunc);
    if(!output)
        throw runtime_error("Error enigma: can't make output file");

    while(getline(input,plainLine))
    {
        encryptedLine="";

        for (int i = 0; i < plainLine.size(); ++i)
            encryptedLine+=encryptChar(plainLine[i]);

        output << encryptedLine << '\n';
    }
}

bool Enigma::validPbFile(const char *fileName) {
    int len=strlen(fileName);
    if (len<4)
        return false;
    else
        return fileName[len-3] == '.' && fileName[len-2] == 'p' && fileName[len-1] == 'b';
}

bool Enigma::validRotorFiles(std::vector<const char *> rotorFiles) {
    int len;
    for (int i = 0; i < rotorFiles.size(); ++i) {
        len = strlen(rotorFiles[i]);
        if (len<5)
            return false;
        if (rotorFiles[i][len-4] != '.' || rotorFiles[i][len-3] != 'r'
            || rotorFiles[i][len-2] != 'o' || rotorFiles[i][len-1] != 't')
            return  false;
    }
    return  true;
}

bool Enigma::validRotSets(const char *rotSets, int nRotors) {
    if (nRotors != strlen(rotSets))
        return false;
    for (int i = 0; i < nRotors; ++i) {
        if (!isalpha(rotSets[i]))
            return false;
    }
    return true;
}


