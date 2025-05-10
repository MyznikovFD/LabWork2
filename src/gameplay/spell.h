#ifndef SPELL_H
#define SPELL_H
#include <iostream>
#include "card.h"

class Spell: public Card {
    std::string description;
    public:
    void describe();
    virtual void pull() = 0;
}
#endif
