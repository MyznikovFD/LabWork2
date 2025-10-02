#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Deck.h"
#include "Hand.h"
#include <algorithm>
#include <utility>
#include <iostream>
#include <string>

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
    
    // Player 1 is always Human, requires renderer
    player1 = std::make_unique<HumanPlayer>("Player 1 (Human)", std::move(deck1), std::move(hand1), renderer);
    
    // Player 2 is Human or AI
    if (mode == GameMode::HUMAN_VS_HUMAN) {
        player2 = std::make_unique<HumanPlayer>("Player 2 (Human)", std::move(deck2), std::move(hand2), renderer);
    } else { // GameMode::HUMAN_VS_AI
        player2 = std::make_unique<AIPlayer>("Player 2 (AI)", std::move(deck2), std::move(hand2), renderer);
    }
}

/**
 * @brief Sets the game mode and initializes players.
 * @param mode The selected mode.
 */
void Game::setGameMode(GameMode mode) {
    // This is called by GameMenu before startGame
    initializePlayers(mode);
}

/**
 * @brief Switches the current player's turn.
 */
void Game::switchTurn() {
    // Only switch if the other player hasn't passed, otherwise the current player keeps turn until the round ends
    if (!otherPlayer->hasPassed()) {
        Player* temp = currentPlayer;
        currentPlayer = otherPlayer;
        otherPlayer = temp;
    }
    // If otherPlayer has passed, the current player continues their turn until they also pass.
}

/**
 * @brief Checks if the round has ended (both players have passed).
 * @return true if the round is over, false otherwise.
 */
bool Game::isRoundOver() const {
    return player1->hasPassed() && player2->hasPassed();
}

/**
 * @brief Starts the game.
 *
 * Initializes decks, deals cards, and begins the replacement phase.
 */
void Game::startGame() {
    // 1. Reset state for the start of a new game
    gameActive = true;
    
    // 2. Initial deck creation (assuming Deck::fillDeck exists)
    player1->getDeck()->fillDeck();
    player2->getDeck()->fillDeck();

    // 3. Draw starting hands (assuming Player::drawStartingHand exists)
    player1->drawStartingHand();
    player2->drawStartingHand();
    
    // 4. Determine starting player (e.g., player1 starts)
    currentPlayer = player1.get();
    otherPlayer = player2.get();

    // 5. Card Replacement Phase
    renderer->displayMessage("\n--- Card Replacement Phase ---");
    processCardReplacement(*player1);
    processCardReplacement(*player2);

    // 6. Initial Game State Rendering
    renderer->displayMessage("\n--- GAME START ---");
}

/**
 * @brief Runs the main game loop.
 */
void Game::runGameLoop() {
    int player1Wins = 0;
    int player2Wins = 0;
    const int MAX_ROUNDS = 3;

    // Check if players were initialized (safeguard)
    if (!player1 || !player2) {
        renderer->displayMessage("Error: Players not initialized. Cannot run game loop.");
        return;
    }

    for (int round = 1; round <= MAX_ROUNDS; ++round) {
        if (player1Wins >= 2 || player2Wins >= 2) {
            break; // Game is over if someone reached 2 wins
        }

        // --- Round Setup ---
        field = GameField(); // Clear the field and reset effects
        player1->unpass();
        player2->unpass();
        
        // Draw one card per round for both players (simplified Gwent rule)
        player1->drawCard();
        player2->drawCard();

        renderer->renderRoundStart(round);
        
        // Ensure starting player is correct for the round (can alternate or be based on previous winner)
        // Alternate starting player for subsequent rounds
        if (round > 1) {
            Player* startingPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
            currentPlayer = startingPlayer;
            otherPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
        }

        // --- Main Turn Loop ---
        while (gameActive && !isRoundOver()) {
            
            // Render state
            renderer->renderGameField(field);
            renderer->renderScores(field.getPlayer1Score(), field.getPlayer2Score());
            renderer->renderHand(currentPlayer->getHand(), currentPlayer == player1.get());
            renderer->renderPassStatus(player1->hasPassed(), player2->hasPassed());
            renderer->renderTurnStart(currentPlayer->getName());

            // Process move (plays card or passes)
            bool moveMade = processTurn();
            
            if (!moveMade) {
                // This means the current player failed to make a valid move (e.g., invalid input for Human)
                // The turn remains with the current player.
                renderer->displayMessage("Invalid action. Please enter a valid card number or 'pass'.");
            }
        }
        
        // --- Round End Logic ---
        int p1Score = field.getPlayer1Score();
        int p2Score = field.getPlayer2Score();
        
        renderer->displayMessage("\n*** Round " + std::to_string(round) + " Results ***");
        
        if (p1Score > p2Score) {
            player1Wins++;
            renderer->displayMessage(player1->getName() + " wins Round " + std::to_string(round) + "!");
        } else if (p2Score > p1Score) {
            player2Wins++;
            renderer->displayMessage(player2->getName() + " wins Round " + std::to_string(round) + "!");
        } else {
            // Draw: both players get a win point (simplified Gwent rule)
            player1Wins++; 
            player2Wins++;
            renderer->displayMessage("Round " + std::to_string(round) + " is a Draw!");
        }
        
        // Final score display for the round (using a renderer method for final score display)
        renderer->renderGameEnd(p1Score, p2Score);

        // Update player wins state
        player1->setWins(player1Wins);
        player2->setWins(player2Wins);
    }
    
    // Set game inactive after the loops finish
    gameActive = false;
}

/**
 * @brief Processes the current player's turn.
 * @return true if a move was made and the game should continue, false otherwise.
 */
bool Game::processTurn() {
    if (currentPlayer->hasPassed()) {
        switchTurn(); // Move to the other player if current one has passed
        return true;
    }

    // Get the card the player wants to play (nullptr if they choose to pass)
    std::shared_ptr<const Card> cardToPlay = currentPlayer->playCard(field);
    
    if (cardToPlay) {
        // A card was played
        
        if (cardToPlay->isSpell()) {
            // If a spell was played, it applies effect and its done
            cardToPlay->applyEffect(field);
        } else {
            // If it's a creature, add it to the field
            bool isPlayer1 = (currentPlayer == player1.get());
            field.addCard(cardToPlay, isPlayer1);
        }
        
        // Card is removed from hand (done inside Player::playCard, but check is for safety)
        if (currentPlayer->getHand().removeCard(cardToPlay)) {
            // Card successfully removed from hand
        } else {
            // Should not happen, but indicates logic error
            renderer->displayMessage("Error: Played card not found in hand!");
            return false;
        }

        // Pass turn
        switchTurn();
        return true;
        
    } else {
        // Player chose to pass (cardToPlay is nullptr returned by Player::playCard)
        // Check if the player is allowed to pass
        if (currentPlayer->decideIfPass()) {
            currentPlayer->pass();
            renderer->displayMessage(currentPlayer->getName() + " passes.");
            switchTurn();
            return true;
        }
        
        // This path is mainly for AI not deciding to pass, or error in HumanPlayer's pass logic.
        return false;
    }
}


/**
 * @brief Processes the initial card replacement phase.
 * @param player The player performing the replacement.
 */
void Game::processCardReplacement(Player& player) {
    // Render hand for context
    renderer->renderHand(player.getHand(), true);
    
    std::vector<std::shared_ptr<const Card>> cardsToReplace;
    
    HumanPlayer* humanPlayer = dynamic_cast<HumanPlayer*>(&player);
    AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(&player);

    if (humanPlayer) {
        // Human logic is handled inside HumanPlayer::selectCardsToReplace, which uses the renderer
        cardsToReplace = humanPlayer->selectCardsToReplace();
    } else if (aiPlayer) {
        // AI logic is handled inside AIPlayer::chooseCardsToReplace
        cardsToReplace = aiPlayer->chooseCardsToReplace();
        // Inform user about AI's choice (required for human player experience)
        if (!cardsToReplace.empty()) {
            std::cout << player.getName() << " replaced " << cardsToReplace.size() << " cards.\n";
        }
    }
    
    player.replaceCards(cardsToReplace);
}

/**
 * @brief Checks the win condition and announces the result.
 */
void Game::checkWinCondition() {
    int p1Wins = player1->getWins();
    int p2Wins = player2->getWins();

    renderer->displayMessage("\n*** FINAL GAME RESULTS ***");
    
    if (p1Wins > p2Wins) {
        renderer->renderWinCondition(player1->getName());
    } else if (p2Wins > p1Wins) {
        renderer->renderWinCondition(player2->getName());
    } else {
        // Use renderGameEnd (which shows scores) for a draw.
        renderer->renderGameEnd(p1Wins, p2Wins); 
    }
}

