#ifndef ENIGMA_COMPONENT_H
#define ENIGMA_COMPONENT_H


class Component
{
public:
    static const int ALPHA_SIZE=26;

    virtual int encrypt(int letter)=0;

    bool wrongInput(int letter);
    void normalizeInt(int &letter);
};

#endif //ENIGMA_COMPONENT_H
