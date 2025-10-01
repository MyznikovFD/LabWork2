/**
 * @file Card.h
 * @brief Defines the abstract base class Card.
 */

#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>

// Forward declaration
class GameField;

/**
 * @brief Abstract base class for all cards in the game.
 *
 * Cards are immutable after creation. Creature cards have baseStrength > 0.
 * Spell cards have baseStrength = 0.
 */
class Card {
private:
    std::string name; ///< The card's name.
    const int baseStrength; ///< The card's base strength (0 for spells).

public:
    /**
     * @brief Constructor.
     * @param cardName The card's name.
     * @param strength The card's base strength.
     */
    Card(const std::string& cardName, int strength);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Card() = default;

    /**
     * @brief Applies the card's effect to the game field (only for spells).
     * @param field The game field to which the effect is applied.
     */
    virtual void applyEffect(GameField& field) const = 0;

    /**
     * @brief Checks if the card is a spell.
     * @return true if the card is a spell, false otherwise.
     */
    virtual bool isSpell() const = 0;

    /**
     * @brief Gets the card's name.
     * @return The card's name.
     */
    const std::string& getName() const 
    { 
        return name; 
    }

    /**
     * @brief Gets the card's base strength.
     * @return The base strength.
     */
    int getBaseStrength() const 
    { 
        return baseStrength; 
    }
};

#endif // CARD_H
