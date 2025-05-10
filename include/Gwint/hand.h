#ifndef HAND_H
#define HAND_H
#include "deck.h"

class Hand {
    Deck deck;
    public:
    void put(Card* card);
    void enum();
}
#endif
