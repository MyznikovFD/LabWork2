/**
 * @file AIPlayer.h
 * @brief Defines the AIPlayer class.
 */

#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "GameRenderer.h"

/**
 * @brief Class representing an AI player.
 *
 * Contains the logic for card selection and pass decisions.
 */
class AIPlayer : public Player {
    std::shared_ptr<GameRenderer> renderer;
public:
    /**
     * @brief Constructor.
     * @param playerName The player's name.
     * @param playerDeck The player's deck.
     * @param playerHand The player's hand.
     */
        AIPlayer(const std::string& playerName, 
             std::unique_ptr<Deck> playerDeck, 
             std::unique_ptr<Hand> playerHand, 
             std::shared_ptr<GameRenderer> renderer);
    /**
     * @brief Selects a card to play based on AI strategy.
     * @return The card selected by the AI, or nullptr if the AI passes.
     */
    std::shared_ptr<const Card> chooseCardToPlay() override;

    /**
     * @brief Decision to pass based on AI strategy.
     * @return true if the AI decides to pass, false otherwise.
     */
    bool decideIfPass() override;

    /**
     * @brief Selects cards for replacement based on AI strategy.
     * @return A list of cards selected by the AI for replacement (up to 2).
     */
    std::vector<std::shared_ptr<const Card>> chooseCardsToReplace() const;
};

#endif // AIPLAYER_H
