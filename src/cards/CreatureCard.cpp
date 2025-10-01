#include "CreatureCard.h"
#include "GameField.h"

/**
 * @brief Constructor.
 * @param cardName The card's name.
 * @param strength The base strength.
 */
CreatureCard::CreatureCard(const std::string& cardName, int strength)
    : Card(cardName, strength) 
{
}

/**
 * @brief Implementation of applyEffect for creatures. Does nothing.
 * @param field The game field (unused).
 */
void CreatureCard::applyEffect(GameField& field) const {
    // Creature cards have no immediate effect upon playing.
}
