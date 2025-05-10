#ifndef CARD_H
#define CARD_H
#include <iostream>

class Card {
    std::string title;
    bool side_battle;
public:
    virtual void describe() = 0;
    virtual void pull() = 0;
}
#endif
