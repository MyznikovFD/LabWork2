// CommanderHorn.h
#ifndef COMMANDERHORN_H
#define COMMANDERHORN_H
#include "Card.h"
#include "GameField.h" 
/**
 * @brief Spell card CommanderHorn.
 *
 * Applies the effect: doubles the strength of all creatures.
 */
class CommanderHorn : public Card {
public:
    CommanderHorn() : Card("CommanderHorn", 0) {}
    void applyEffect(GameField& field) const override;
    bool isSpell() const override 
    { 
        return true; 
    }
};
#endif // COMMANDERHORN_H
