// Archer.h
#ifndef ARCHER_H
#define ARCHER_H
#include "CreatureCard.h"
/** @brief Creature card Archer (strength 4). */
class Archer : public CreatureCard {
public: Archer() : CreatureCard("Archer", 4) {}
};
#endif // ARCHER_H
