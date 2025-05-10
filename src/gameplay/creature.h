#ifndef CREATURE_H
#define CREATURE_H
#include "card.h"
#include "special_ability.h"

class Creature: public Card {
    int basic_force;
    int active_force = 0;
    special_ability spAb;
    public:
    /// The method returns number which is equal to the active force
    int get_active_force();
    /// The method sets new active force
    void set_actve_force(int new_force);
    /// 
    void pull();
}
#endif
