#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include "GameRenderer.h" // New dependency

class Deck;
class Hand;
class Card;

/**
 * @brief Class representing a human player.
 */
class HumanPlayer : public Player {
private:
    std::shared_ptr<GameRenderer> renderer; // Added for I/O

public:
    /**
     * @brief Constructor.
     * @param playerName The player's name.
     * @param playerDeck The player's deck.
     * @param playerHand The player's hand.
     * @param renderer The game renderer for I/O.
     */
    HumanPlayer(const std::string& playerName, std::unique_ptr<Deck> playerDeck, std::unique_ptr<Hand> playerHand, std::shared_ptr<GameRenderer> renderer); // Updated signature

    std::shared_ptr<const Card> chooseCardToPlay() override;
    bool decideIfPass() override;
    std::vector<std::shared_ptr<const Card>> selectCardsToReplace() const;
};

#endif // HUMANPLAYER_H
