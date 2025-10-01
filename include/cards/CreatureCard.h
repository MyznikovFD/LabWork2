/**
 * @file CreatureCard.h
 * @brief Defines the base class for creature cards.
 */

#ifndef CREATURECARD_H
#define CREATURECARD_H

#include "Card.h"

/**
 * @brief Base class for creature cards.
 *
 * Creature cards do not have an immediate effect upon playing; their strength
 * is calculated by GameField.
 */
class CreatureCard : public Card {
public:
    /**
     * @brief Constructor.
     * @param cardName The card's name.
     * @param strength The base strength.
     */
    CreatureCard(const std::string& cardName, int strength);

    /**
     * @brief Implementation of applyEffect for creatures. Does nothing.
     * @param field The game field (unused).
     */
    void applyEffect(GameField& field) const override;

    /**
     * @brief Identifies the card as not a spell.
     * @return false.
     */
    bool isSpell() const override 
    { 
        return false; 
    }
};

#endif // CREATURECARD_H
