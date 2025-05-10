#ifndef HAND_H
#define HAND_H
#include "deck.h"

class Hand: public Deck {
    Deck deck;
    public:
    /// Puts some card on the game field
    void pull_out(Card* card);
    /// Pulls out some quantity of cards from the deck
    void pullout_cards(int amount = 1);
    /// Returns vector of cards remaining in hand
    std::vector<int> enum_ids();
}
#endif
