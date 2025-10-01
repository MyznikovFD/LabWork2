/**
 * @file GameMenu.h
 * @brief Defines the GameMenu class for managing the game mode selection menu.
 */

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <memory>
#include "Game.h"
#include "GameRenderer.h"

/**
 * @brief Class managing the main menu and game mode selection.
 */
class GameMenu {
private:
    std::unique_ptr<Game> game; ///< Game instance.
    std::shared_ptr<GameRenderer> renderer; ///< Renderer for displaying the menu.

public:
    /**
     * @brief Constructor.
     * @param gameRenderer The renderer.
     */
    GameMenu(std::shared_ptr<GameRenderer> gameRenderer);

    /**
     * @brief Displays the main menu and handles user selection.
     */
    void showMainMenu();

    /**
     * @brief Initializes the game with the selected mode.
     * @param mode The selected game mode.
     */
    void selectGameMode(GameMode mode);

    /**
     * @brief Starts the game.
     */
    void startGame();
};

#endif // GAMEMENU_H
