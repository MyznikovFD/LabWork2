/**
 * @file Hand.h
 * @brief Defines the Hand class for managing cards in a player's hand.
 */

#ifndef HAND_H
#define HAND_H

#include <vector>
#include <memory>
#include "Card.h"

/**
 * @brief Class representing a player's hand.
 *
 * Responsible for storing, adding, and removing cards from the hand.
 */
class Hand {
private:
    std::vector<std::shared_ptr<const Card>> cards; ///< Cards in the hand.

public:
    /**
     * @brief Adds a card to the hand.
     * @param card The card to add.
     */
    void addCard(std::shared_ptr<const Card> card);

    /**
     * @brief Removes a card from the hand.
     * @param card The card to remove (compares pointers).
     * @return true if the card was successfully removed, false otherwise.
     */
    bool removeCard(const std::shared_ptr<const Card>& card);

    /**
     * @brief Gets the list of cards in the hand.
     * @return Constant reference to the vector of cards.
     */
    const std::vector<std::shared_ptr<const Card>>& getCards() const
    { 
        return cards; 
    }

    /**
     * @brief Gets the number of cards in the hand.
     * @return The size of the hand.
     */
    int getSize() const
    { 
        return static_cast<int>(cards.size()); 
    }
};

#endif // HAND_H
