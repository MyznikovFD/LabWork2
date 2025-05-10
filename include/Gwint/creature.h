#ifndef CREATURE_H
#define CREATURE_H
#include "card.h"
#include "special_ability.h"

class Creature: public Card {
    int strength;
    special_ability spAb;
    public:
    void describe();
    void pull();
}
#endif
