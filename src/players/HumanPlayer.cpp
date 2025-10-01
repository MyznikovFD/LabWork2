/**
 * @file HumanPlayer.h
 * @brief Defines the HumanPlayer class.
 */

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

/**
 * @brief Class representing a human player.
 *
 * In a real implementation, it will interact with GameRenderer for input.
 */
class HumanPlayer : public Player {
public:
    /**
     * @brief Constructor.
     * @param playerName The player's name.
     * @param playerDeck The player's deck.
     * @param playerHand The player's hand.
     */
    HumanPlayer(const std::string& playerName, std::unique_ptr<Deck> playerDeck, std::unique_ptr<Hand> playerHand);

    /**
     * @brief Selects a card to play (requires user input).
     * @return The card selected by the user, or nullptr if the user passes.
     */
    std::shared_ptr<const Card> chooseCardToPlay() override;

    /**
     * @brief Decision to pass (requires user input).
     * @return true if the user decides to pass, false otherwise.
     */
    bool decideIfPass() override;

    /**
     * @brief Selects cards for replacement (requires user input).
     * @return A list of cards selected for replacement.
     */
    std::vector<std::shared_ptr<const Card>> selectCardsToReplace() const;
};

#endif // HUMANPLAYER_H
