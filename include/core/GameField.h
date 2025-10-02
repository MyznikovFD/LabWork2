/**
 * @file GameField.h
 * @brief Defines the GameField class, which manages the field, cards, and score calculation.
 */

#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include <memory>
#include "Card.h"

/**
 * @brief Represents the game board.
 *
 * Responsible for storing played cards, tracking active weather effects,
 * and calculating players' current scores.
 */
class GameField {
private:
    std::vector<std::shared_ptr<const Card>> player1Cards; ///< Cards played by Player 1.
    std::vector<std::shared_ptr<const Card>> player2Cards; ///< Cards played by Player 2.
    bool commanderHornActive; ///< Flag for CommanderHorn effect activity.
    bool bitingFrostActive;   ///< Flag for BitingFrost effect activity.

    /**
     * @brief Calculates the effective strength of a single card considering active effects.
     * @param card The card to calculate strength for.
     * @return The card's current effective strength.
     */
    int calculateCardStrength(const std::shared_ptr<const Card>& card) const;

public:
    /**
     * @brief Default constructor.
     */
    GameField();

    /**
     * @brief Adds a played card to the field.
     * @param card The card to add.
     * @param isPlayer1 Flag indicating if the card was played by Player 1.
     */
    void addCard(std::shared_ptr<const Card> card, bool isPlayer1);

    /**
     * @brief Sets the activity status of the CommanderHorn effect.
     * @param active The new activity state.
     */
    void setCommanderHornActive(bool active);

    /**
     * @brief Sets the activity status of the BitingFrost effect.
     * @param active The new activity state.
     */
    void setBitingFrostActive(bool active);
    /**
     * @brief Checks if CommanderHorn is active.
     * @return true if CommanderHorn is active.
     */

    bool isCommanderHornActive() const
    { 
        return commanderHornActive; 
    }

    /**
     * @brief Checks if BitingFrost is active.
     * @return true if BitingFrost is active.
     */
    bool isBitingFrostActive() const
    { 
        return bitingFrostActive; 
    }

    /**
     * @brief Clears weather effects (specifically BitingFrost).
     */
    void clearWeatherEffects();

    /**
     * @brief Calculates Player 1's total score considering active effects.
     * @return Player 1's total score.
     */
    int getPlayer1Score() const;

    /**
     * @brief Calculates Player 2's total score considering active effects.
     * @return Player 2's total score.
     */
    int getPlayer2Score() const;
    
    /**
     * @brief Gets the list of cards played by Player 1.
     * @return Constant reference to the vector of Player 1's cards.
     */
    const std::vector<std::shared_ptr<const Card>>& getPlayer1Cards() const
    { 
        return player1Cards; 
    }
    
    /**
     * @brief Gets the list of cards played by Player 2.
     * @return Constant reference to the vector of Player 2's cards.
     */
    const std::vector<std::shared_ptr<const Card>>& getPlayer2Cards() const
    { 
        return player2Cards; 
    }
};

#endif // GAMEFIELD_H
