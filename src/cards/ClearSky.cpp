// ClearSky.h
#ifndef CLEARSKY_H
#define CLEARSKY_H
#include "Card.h"
#include "GameField.h"
/**
 * @brief Spell card ClearSky.
 *
 * Applies the effect: removes the BitingFrost effect.
 */
class ClearSky : public Card {
public:
    ClearSky() : Card("ClearSky", 0) {}
    void applyEffect(GameField& field) const override;
    bool isSpell() const override 
    { 
        return true; 
    }
};
#endif // CLEARSKY_H
