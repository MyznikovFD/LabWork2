#ifndef CARD_H
#define CARD_H
#include <string>

class Card {
    std::string title;
    int id;
public:
    virtual void pull() = 0;
}
#endif
