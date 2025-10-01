#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include <algorithm>
#include <utility>

/**
 * @brief Constructor.
 * @param playerName The player's name.
 * @param playerDeck The deck associated with the player.
 * @param playerHand The hand associated with the player.
 */
Player::Player(const std::string& playerName, std::unique_ptr<Deck> playerDeck, std::unique_ptr<Hand> playerHand)
    : name(playerName), hand(std::move(playerHand)), deck(std::move(playerDeck)), hasPassed(false)
{
}

/**
 * @brief Allows the player to replace cards.
 * @param cardsToReplace List of cards from the hand to be replaced.
 */
void Player::replaceCards(const std::vector<std::shared_ptr<const Card>>& cardsToReplace) {
    if (cardsToReplace.empty()) return;

    // 1. Remove cards from hand
    for (const auto& card : cardsToReplace) {
        hand->removeCard(card);
    }
    
    // 2. Return cards to deck
    deck->returnCards(cardsToReplace);
    deck->shuffle(); // Reshuffle deck before drawing to ensure "different random cards" are drawn from an updated deck.

    // 3. Draw new, different cards
    int count = static_cast<int>(cardsToReplace.size());
    // The implementation of drawDifferentCards ensures that the *returned* cards
    // are not immediately drawn again, even if they are in the deck (they are checked against the excluded list).
    std::vector<std::shared_ptr<const Card>> newCards = deck->drawDifferentCards(count, cardsToReplace);
    
    // 4. Add new cards to hand
    for (auto& card : newCards) {
        hand->addCard(std::move(card));
    }
}

/**
 * @brief Declares that the player is passing.
 */
void Player::pass() {
    hasPassed = true;
}

/**
 * @brief Automatically passes the player if they have no cards left.
 * @return true if the player automatically passed, false otherwise.
 */
bool Player::autoPassIfNoCards() {
    if (!hasPassed && hand->getSize() == 0) {
        pass();
        return true;
    }
    return false;
}
