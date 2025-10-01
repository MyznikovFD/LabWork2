/**
 * @file Deck.h
 * @brief Defines the Deck class for managing the deck.
 */

#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <ctime>
#include "Card.h"
// Include all concrete card types for Deck initialization
#include "CroneWhispess.h"
#include "CroneWeavess.h"
#include "CroneBrewess.h"
#include "Catapult.h"
#include "SiegeExpert.h"
#include "BlueStripesCommando.h"
#include "CloseCombat.h"
#include "Archer.h"
#include "CommanderHorn.h"
#include "BitingFrost.h"
#include "ClearSky.h"

/**
 * @brief Class representing a player's deck.
 *
 * Responsible for initialization, shuffling, drawing cards, and card replacement.
 */
class Deck {
private:
    std::vector<std::shared_ptr<const Card>> cards; ///< Cards currently in the deck.

    /**
     * @brief Creates a complete, static template deck of 11 unique cards.
     * @return A vector containing the 11 cards.
     */
    static std::vector<std::shared_ptr<const Card>> createFullDeckTemplate();

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the deck with 11 unique cards.
     */
    Deck();

    /**
     * @brief Initializes the deck with 11 unique cards by copying the template.
     */
    void initializeDeck();

    /**
     * @brief Shuffles the deck.
     */
    void shuffle();

    /**
     * @brief Draws (removes and returns) the top card from the deck.
     * @return Pointer to the drawn card, or nullptr if the deck is empty.
     */
    std::shared_ptr<const Card> drawCard();

    /**
     * @brief Draws a specified number of *different* random cards, excluding
     * the provided list (for replacement logic).
     * @param count The number of cards to draw.
     * @param excluded List of cards that should not be drawn (e.g., those just replaced).
     * @return A list of drawn cards.
     */
    std::vector<std::shared_ptr<const Card>> drawDifferentCards(int count, const std::vector<std::shared_ptr<const Card>>& excluded);

    /**
     * @brief Returns cards back to the deck (for replacement).
     * @param cardsToReturn List of cards to return.
     */
    void returnCards(const std::vector<std::shared_ptr<const Card>>& cardsToReturn);
};

#endif // DECK_H
