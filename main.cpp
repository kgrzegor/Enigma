#include <iostream>
#include <vector>

#include "Enigma.h"

using  namespace std;

int main(int argc, char **argv) {
    if (argc<6) {
        cerr << "Please run this program with arguments <msg> <encryped msg> <*.pb> <[*.rot]> <rot sets>"
             << endl << "<msg.txt>: text file with message to encrypt"
             << endl << "<encypted msg.txt>: destination file with encryped message"
             << endl << "<*.pb>: required plugboard file"
             << endl << "<[*.rot]>: list of rotor files"
             << endl << "<[rot sets]>: starting position for rotors";
        exit(1);
    }
    const char *inputFile=argv[1];
    const char *outputFile=argv[2];
    const char *pbFile=argv[3];
    vector<const char*> rotorFiles;
    const char *rotSets = argv[argc-1];

    for (int i = 4; i < argc-1; ++i)
        rotorFiles.push_back(argv[i]);

    try {
        Enigma enigmaMachine(pbFile,rotorFiles,rotSets);
        enigmaMachine.encryptFile(inputFile,outputFile);
    }
    catch (runtime_error e){
        cerr << e.what() << endl;
    }
    return 0;
}