#ifndef SPECIAL_ABILITIES_H
#define SPECIAL_ABILITIES_H
#include <iostream>

class Special_ability {
    std::string description;
    public:
    void describe();
    virtual void interact() = 0;
};


#ifndef DOPPELGANGER_H
#define DOPPELGANGER_H
class Doppelganger {
    public:
    void interact();
}
#endif

#ifndef MEDIC_H
#define MEDIC_H


class Medic : public Special_ability {
    public:
    void interact();
}
#endif

#ifndef SPY_H
#define SPY_H


class Spy : public Special_ability {
    public:
    void interact();
}
#endif


#ifndef SURGE_OF_STRENGTH_H
#define SURGE_OF_STRENGTH_H


class Surge_of_strength : public Special_ability {
    public:
    void interact();
}
#endif

#ifndef USE_SPELL_H
#define USE_SPELL_H

#include "line_spell.h"

class Use_spell : public Special_ability {
    Line_spell spell;
    public:
    void interact();
}
#endif
#endif
