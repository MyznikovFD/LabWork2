#include <vector>
#include <random>
#include "card.h"

std::vector<Card*> Deck::choose_random_cards(int amount = 1) {
    std::vector<Card*> pulling_cards(amount);
    int deck_size = cards.size();
    std::random_device rd;
    int random_number;
    
    for (int i = 0, i < amount, i++) {
        if (deck_size - i > 0) {
            random_number = rd() % (deck_size - i)
            pulling_cards.push_back( cards[random_number] );
            cards.erase[random_number];
        }
    } 
    return pulling_cards;
};

void Deck::pull_card(Card* card) {
    cards.push_back(card);
};
