#include "Card.h"

/**
 * @brief Constructor.
 * @param cardName The card's name.
 * @param strength The card's base strength.
 */
Card::Card(const std::string& cardName, int strength) 
    : name(cardName), baseStrength(strength) 
{
}
