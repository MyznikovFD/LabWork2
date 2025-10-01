#include "Deck.h"
#include <random>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <utility>

/**
 * @brief Creates a complete, static template deck of 11 unique cards.
 * @return A vector containing the 11 cards.
 */
std::vector<std::shared_ptr<const Card>> Deck::createFullDeckTemplate() {
    std::vector<std::shared_ptr<const Card>> templateDeck;
    
    // Creatures (8 cards)
    templateDeck.push_back(std::make_shared<const CroneWhispess>());
    templateDeck.push_back(std::make_shared<const CroneWeavess>());
    templateDeck.push_back(std::make_shared<const CroneBrewess>());
    templateDeck.push_back(std::make_shared<const Catapult>());
    templateDeck.push_back(std::make_shared<const SiegeExpert>());
    templateDeck.push_back(std::make_shared<const BlueStripesCommando>());
    templateDeck.push_back(std::make_shared<const CloseCombat>());
    templateDeck.push_back(std::make_shared<const Archer>());
    
    // Spells (3 cards)
    templateDeck.push_back(std::make_shared<const CommanderHorn>());
    templateDeck.push_back(std::make_shared<const BitingFrost>());
    templateDeck.push_back(std::make_shared<const ClearSky>());
    
    return templateDeck;
}

/**
 * @brief Default constructor.
 */
Deck::Deck() {
    initializeDeck();
    shuffle();
}

/**
 * @brief Initializes the deck with 11 unique cards by copying the template.
 */
void Deck::initializeDeck() {
    cards = createFullDeckTemplate();
}

/**
 * @brief Shuffles the deck.
 */
void Deck::shuffle() {
    unsigned seed = static_cast<unsigned>(std::time(0));
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

/**
 * @brief Draws (removes and returns) the top card from the deck.
 * @return Pointer to the drawn card, or nullptr if the deck is empty.
 */
std::shared_ptr<const Card> Deck::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }
    std::shared_ptr<const Card> drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

/**
 * @brief Draws a specified number of *different* random cards, excluding the provided list.
 * @param count The number of cards to draw.
 * @param excluded List of cards that should not be drawn.
 * @return A list of drawn cards.
 */
std::vector<std::shared_ptr<const Card>> Deck::drawDifferentCards(int count, const std::vector<std::shared_ptr<const Card>>& excluded) {
    std::vector<std::shared_ptr<const Card>> drawnCards;
    
    // Find all cards in the deck that are NOT in the excluded list
    std::vector<std::shared_ptr<const Card>> availableToDraw;
    for (const auto& deckCard : cards) {
        bool isExcluded = false;
        // Compare card pointers to check exclusion
        if (std::find(excluded.begin(), excluded.end(), deckCard) != excluded.end()) {
            isExcluded = true;
        }
        
        if (!isExcluded) {
            availableToDraw.push_back(deckCard);
        }
    }
    
    // Adjust count if not enough unique cards are available
    if (availableToDraw.empty() || count > static_cast<int>(availableToDraw.size())) {
        count = static_cast<int>(availableToDraw.size());
    }

    if (count == 0) return {};

    // Shuffle the available cards to ensure random selection
    unsigned seed = static_cast<unsigned>(std::time(0));
    std::shuffle(availableToDraw.begin(), availableToDraw.end(), std::default_random_engine(seed));

    // Select the required count
    for (int i = 0; i < count; ++i) {
        drawnCards.push_back(availableToDraw[i]);
    }
    
    // Remove drawn cards from the actual deck
    for (const auto& drawnCard : drawnCards) {
        auto it = std::find(cards.begin(), cards.end(), drawnCard);
        if (it != cards.end()) {
            cards.erase(it);
        }
    }
    
    return drawnCards;
}

/**
 * @brief Returns cards back to the deck (for replacement).
 * @param cardsToReturn List of cards to return.
 */
void Deck::returnCards(const std::vector<std::shared_ptr<const Card>>& cardsToReturn) {
    for (const auto& card : cardsToReturn) {
        cards.push_back(card);
    }
}
