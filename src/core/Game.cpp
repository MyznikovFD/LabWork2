#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Deck.h"
#include "Hand.h"
#include <algorithm>
#include <utility>
#include <iostream>

/**
 * @brief Constructor.
 * @param gameRenderer The renderer used for user/AI interaction.
 */
Game::Game(std::shared_ptr<GameRenderer> gameRenderer)
    : gameActive(false), currentMode(GameMode::HUMAN_VS_AI), 
      currentPlayer(nullptr), otherPlayer(nullptr), renderer(std::move(gameRenderer))
{
}

/**
 * @brief Helper method to initialize players after mode selection.
 * @param mode The selected game mode.
 */
void Game::initializePlayers(GameMode mode) {
    currentMode = mode;
    
    // Create Deck and Hand objects
    std::unique_ptr<Deck> deck1 = std::make_unique<Deck>();
    std::unique_ptr<Hand> hand1 = std::make_unique<Hand>();
    
    std::unique_ptr<Deck> deck2 = std::make_unique<Deck>();
    std::unique_ptr<Hand> hand2 = std::make_unique<Hand>();
    
    // Player 1 is always Human
    player1 = std::make_unique<HumanPlayer>("Player 1 (Human)", std::move(deck1), std::move(hand1));
    
    // Player 2 is Human or AI
    if (mode == GameMode::HUMAN_VS_HUMAN) {
        player2 = std::make_unique<HumanPlayer>("Player 2 (Human)", std::move(deck2), std::move(hand2));
    } else { // HUMAN_VS_AI
        player2 = std::make_unique<AIPlayer>("Player 2 (AI)", std::move(deck2), std::move(hand2));
    }
    
    // Player 1 starts
    currentPlayer = player1.get();
    otherPlayer = player2.get();
}

/**
 * @brief Sets the game mode.
 * @param mode The selected mode.
 */
void Game::setGameMode(GameMode mode) {
    initializePlayers(mode);
}

/**
 * @brief Starts the game.
 */
void Game::startGame() {
    if (!player1 || !player2) {
        // Should not happen if setGameMode was called, but as a safeguard
        setGameMode(GameMode::HUMAN_VS_AI);
    }
    
    // 1. Deal 7 cards (Decks are already initialized and shuffled in their constructor)
    for (int i = 0; i < 7; ++i) {
        player1->getHand().addCard(player1->getDeck().drawCard());
        player2->getHand().addCard(player2->getDeck().drawCard());
    }
    
    // 2. Process card replacement
    processCardReplacement(*player1);
    
    // Player 2 replacement: Human or AI logic
    processCardReplacement(*player2);
    
    gameActive = true;
}

/**
 * @brief Runs the main game loop.
 */
void Game::runGameLoop() {
    while (gameActive) {
        if (isRoundOver()) {
            break;
        }

        // Check for auto-pass (no cards left)
        if (currentPlayer->autoPassIfNoCards()) {
            // Renderer output should inform the player of auto-pass
            renderer->renderPassStatus(player1->getHasPassed(), player2->getHasPassed());
            switchTurn();
            continue;
        }
        
        if (!currentPlayer->getHasPassed()) {
            // Process current player's action (play card or pass)
            processTurn();
        } else {
            // If current player has already passed, skip turn and switch
            switchTurn();
        }

        // Always render status after a turn is completed
        renderer->renderGameField(field);
        renderer->renderScores(field.getPlayer1Score(), field.getPlayer2Score());
        renderer->renderHand(player1->getHand(), true);
        renderer->renderHand(player2->getHand(), (player2.get() == player1.get())); // Hide AI hand
        renderer->renderPassStatus(player1->getHasPassed(), player2->getHasPassed());
    }
    gameActive = false;
}

/**
 * @brief Checks if the round has ended (both players have passed).
 * @return true if the round is over, false otherwise.
 */
bool Game::isRoundOver() const {
    // Round ends when both players have passed
    return player1->getHasPassed() && player2->getHasPassed();
}

/**
 * @brief Switches the current player's turn.
 */
void Game::switchTurn() {
    std::swap(currentPlayer, otherPlayer);
}

/**
 * @brief Processes the current player's turn.
 * @return true if a move was made and the game should continue, false otherwise.
 */
bool Game::processTurn() {
    // 1. Get action from Player (card or pass)
    // The player's method handles the play/pass decision internally
    std::shared_ptr<const Card> cardToPlay = currentPlayer->chooseCardToPlay();
    
    if (cardToPlay) {
        // Player chose to play a card
        
        // Remove card from hand
        if (!currentPlayer->getHand().removeCard(cardToPlay)) {
            // Should not happen if Player::chooseCardToPlay is implemented correctly
            return false;
        }

        // Apply card effect
        cardToPlay->applyEffect(field);

        // Place card on field (if it's a creature card, GameField::addCard handles the check)
        bool isPlayer1 = (currentPlayer == player1.get());
        field.addCard(cardToPlay, isPlayer1);
        
        // Pass turn
        switchTurn();
        return true;
        
    } else {
        // Player chose to pass (cardToPlay is nullptr)
        if (currentPlayer->decideIfPass()) {
            currentPlayer->pass();
            switchTurn();
            return true;
        }
        
        // The player's method returned nullptr but decideIfPass() said no pass.
        // This means the player wants to cancel the pass and re-select (not supported in this stub).
        return false;
    }
}

/**
 * @brief Processes the initial card replacement phase.
 * @param player The player performing the replacement.
 */
void Game::processCardReplacement(Player& player) {
    // STUB: Logic for card replacement
    
    std::vector<std::shared_ptr<const Card>> cardsToReplace;
    
    HumanPlayer* humanPlayer = dynamic_cast<HumanPlayer*>(&player);
    AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(&player);

    if (humanPlayer) {
        // STUB: Requires renderer interaction
        cardsToReplace = renderer->renderCardReplacementInterface(humanPlayer->getHand());
    } else if (aiPlayer) {
        // AI logic
        cardsToReplace = aiPlayer->chooseCardsToReplace();
    }
    
    player.replaceCards(cardsToReplace);
}

/**
 * @brief Checks the win condition and announces the result.
 */
void Game::checkWinCondition() {
    int score1 = field.getPlayer1Score();
    int score2 = field.getPlayer2Score();
    
    std::string winnerName;
    if (score1 > score2) {
        winnerName = player1->getName();
    } else if (score2 > score1) {
        winnerName = player2->getName();
    } else {
        winnerName = "It's a tie!";
    }

    renderer->renderWinCondition(winnerName);
}
