
/**
 * @file Game.h
 * @brief Defines the Game class, managing the overall game process.
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include "GameField.h"
#include "Player.h"
#include "GameRenderer.h"
#include "Deck.h"
#include "Hand.h"
#include "GameMode.h"

// --- PRELIMINARY DECLARATION ---
class Player;
class HumanPlayer;
class AIPlayer;
class Card;

/**
 * @brief Class controlling the main game flow.
 *
 * Responsible for initialization, turn management, win condition checks,
 * and the card replacement phase.
 */
class Game {
private:
    std::unique_ptr<Player> player1; ///< Player 1 (Human).
    std::unique_ptr<Player> player2; ///< Player 2 (Human or AI).
    GameField field; ///< The game board.
    bool gameActive; ///< Flag for game activity.
    GameMode currentMode; ///< The current game mode.
    Player* currentPlayer; ///< Pointer to the player whose turn it is.
    Player* otherPlayer; ///< Pointer to the other player.

    std::shared_ptr<GameRenderer> renderer; ///< Renderer for displaying state.

    /**
     * @brief Helper method to initialize players after mode selection.
     * @param mode The selected game mode.
     */
    void initializePlayers(GameMode mode);

    /**
     * @brief Switches the current player's turn.
     */
    void switchTurn();

    /**
     * @brief Checks if the round has ended (both players have passed).
     * @return true if the round is over, false otherwise.
     */
    bool isRoundOver() const;

    /**
     * @brief Processes the current player's turn.
     * @return true if a move was made and the game should continue, false otherwise.
     */
    bool processTurn();

public:
    /**
     * @brief Constructor.
     * @param gameRenderer The renderer used for user/AI interaction.
     */
    Game(std::shared_ptr<GameRenderer> gameRenderer);

    /**
     * @brief Sets the game mode.
     * @param mode The selected mode.
     */
    void setGameMode(GameMode mode);

    /**
     * @brief Starts the game.
     *
     * Initializes decks, deals cards, and begins the replacement phase.
     */
    void startGame();

    /**
     * @brief Runs the main game loop.
     */
    void runGameLoop();

    /**
     * @brief Processes the initial card replacement phase.
     * @param player The player performing the replacement.
     */
    void processCardReplacement(Player& player);

    /**
     * @brief Checks the win condition and announces the result.
     */
    void checkWinCondition();

    // Accessors for Game state (if needed for testing/renderer)
    Player* getPlayer1() const { return player1.get(); }
    Player* getPlayer2() const { return player2.get(); }
    GameField& getField() { return field; }
};

#endif // GAME_H
