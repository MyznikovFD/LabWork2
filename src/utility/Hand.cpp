#include "Hand.h"
#include <algorithm>
#include <utility>

/**
 * @brief Adds a card to the hand.
 * @param card The card to add.
 */
void Hand::addCard(std::shared_ptr<const Card> card) {
    cards.push_back(std::move(card));
}

/**
 * @brief Removes a card from the hand.
 * @param card The card to remove (compares pointers).
 * @return true if the card was successfully removed, false otherwise.
 */
bool Hand::removeCard(const std::shared_ptr<const Card>& card) {
    auto it = std::find(cards.begin(), cards.end(), card);
    if (it != cards.end()) {
        cards.erase(it);
        return true;
    }
    return false;
}
