// BitingFrost.h
#ifndef BITINGFROST_H
#define BITINGFROST_H
#include "Card.h"
#include "GameField.h"
/**
 * @brief Spell card BitingFrost.
 *
 * Applies the effect: sets the strength of all creatures to 1.
 */
class BitingFrost : public Card {
public:
    BitingFrost() : Card("BitingFrost", 0) {}
    void applyEffect(GameField& field) const override;
    bool isSpell() const override 
    { 
        return true; 
    }
};
#endif // BITINGFROST_H
