#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"

class Deck {
    vector<Card*> cards;
    public:
    /// Removes some quantity of cards from the deck and returns them
    std::vector<Card*> choose_random_cards(int amount = 1);
    
    /// Pulls some card into the deck
    void pull_card(Card* card);
}
#endif
