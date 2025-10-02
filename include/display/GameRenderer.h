/**
 * @file GameRenderer.h
 * @brief Defines the abstract base class GameRenderer for displaying game state and handling input.
 */

#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <vector>
#include <memory>
#include "Hand.h"
#include "GameField.h"
#include "GameMode.h"
#include "Card.h" // Убеждаемся, что Card доступен для shared_ptr

// Forward declaration
class GameMenu;

/**
 * @brief Abstract class responsible for rendering the game state and user interaction.
 *
 * This allows for a console, GUI, or other type of interface implementation.
 */
class GameRenderer {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~GameRenderer() = default;

    /**
     * @brief Renders the main menu (output only).
     */
    virtual void renderMainMenu() = 0;

    /**
     * @brief Renders the game mode selection menu and receives the user's choice (I/O).
     * @return The selected GameMode.
     */
    virtual GameMode renderGameModeSelection() = 0; // NON-CONST

    /**
     * @brief Renders the current state of the game field (output only).
     * @param field The game field.
     */
    virtual void renderGameField(const GameField& field) = 0;

    /**
     * @brief Renders the cards in the player's hand (output only).
     * @param hand The player's hand.
     * @param isHuman Flag indicating if the player is human (for hiding AI cards).
     */
    virtual void renderHand(const Hand& hand, bool isHuman) = 0;

    /**
     * @brief Renders the current scores of the players (output only).
     */
    virtual void renderScores(int player1Score, int player2Score) = 0;

    /**
     * @brief Renders the players' pass status (output only).
     */
    virtual void renderPassStatus(bool player1Passed, bool player2Passed) = 0;

    /**
     * @brief Renders the interface for card replacement and receives the user's choice (I/O).
     * @param hand The player's hand.
     * @return A list of cards selected for replacement (up to 2).
     */
    virtual std::vector<std::shared_ptr<const Card>> renderCardReplacementInterface(const Hand& hand) = 0; // NON-CONST

    /**
     * @brief Prompts the human player for a card selection or a pass (I/O).
     * @param hand The player's hand.
     * @param isPassOptionAvailable Whether the player can choose to pass.
     * @return The selected card, or nullptr for a pass.
     */
    virtual std::shared_ptr<const Card> promptPlayerTurn(const Hand& hand, bool isPassOptionAvailable) = 0; // NON-CONST

    /**
     * @brief Renders the winner announcement (output only).
     */
    virtual void renderWinCondition(const std::string& winnerName) = 0;
};

#endif // GAMERENDERER_H

