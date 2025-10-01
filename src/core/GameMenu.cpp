#include "GameMenu.h"
#include <iostream>

/**
 * @brief Constructor.
 * @param gameRenderer The renderer.
 */
GameMenu::GameMenu(std::shared_ptr<GameRenderer> gameRenderer) 
    : renderer(std::move(gameRenderer)) 
{
    // The Game object lazily created in selectGameMode.
}

/**
 * @brief Displays the main menu and handles user selection.
 */
void GameMenu::showMainMenu() {
    // STUB: Interface implementation is deferred
    renderer->renderMainMenu();
    GameMode mode = renderer->renderGameModeSelection();
    
    selectGameMode(mode);
}

/**
 * @brief Initializes the game with the selected mode.
 * @param mode The selected game mode.
 */
void GameMenu::selectGameMode(GameMode mode) {
    // Create the Game instance, passing the renderer
    game = std::make_unique<Game>(renderer);
    game->setGameMode(mode);
}

/**
 * @brief Starts the game.
 */
void GameMenu::startGame() {
    if (!game) {
        // Fallback if the game was not initialized (should not happen with proper flow)
        selectGameMode(GameMode::HUMAN_VS_AI);
    }
    
    // Start game phases
    game->startGame();
    game->runGameLoop();
    // After the loop, check the final win condition
    game->checkWinCondition();
}
