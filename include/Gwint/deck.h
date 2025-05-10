#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"

class Deck {
    vector<Card*> cards;
    public:
    /// Pulls out a card from the deck
    void pullout_card();

    /// Pulls out some quantity of cards from the deck
    void pullout_cards(int amount);
    
    /// Pulls some card into the deck
    void pullin_card(Card* card);
}
#endif
