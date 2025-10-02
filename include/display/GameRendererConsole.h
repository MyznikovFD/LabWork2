/**
 * @file GameRendererConsole.h
 * @brief Defines the GameRendererConsole class for console pseudographic output and user input handling.
 */

#ifndef GAMERENDERERCONSOLE_H
#define GAMERENDERERCONSOLE_H

#include "GameRenderer.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

/**
 * @brief Concrete implementation of GameRenderer using console pseudographics.
 */
class GameRendererConsole : public GameRenderer {
private:
    /**
     * @brief Centralized function for getting string input from console.
     * * All work with std::cin happens only here, which supports SRP.
     * @return Input string converted to lowercase.
     */
    std::string getInput();

    /**
     * @brief Renders help message about effects and commands.
     */
    void renderHelp() const;

    /**
     * @brief Renders individual card block (pseudographics).
     * @param card Card to render.
     * @param index Card index/number (>0 for hand, 0 for field).
     * @param showIndex True if index should be displayed.
     * @return Vector of strings representing the card block line by line.
     */
    std::vector<std::string> renderCardBox(const std::shared_ptr<const Card>& card, int index, bool showIndex) const;

public:
    GameRendererConsole() = default;

    // --- Methods inherited from GameRenderer ---
    void renderMainMenu() override;
    GameMode renderGameModeSelection() override;
    void renderGameField(const GameField& field) override;
    void renderHand(const Hand& hand, bool isHuman) override;
    void renderScores(int player1Score, int player2Score) override;
    void renderPassStatus(bool player1Passed, bool player2Passed) override;
    std::vector<std::shared_ptr<const Card>> renderCardReplacementInterface(const Hand& hand) override;
    std::shared_ptr<const Card> promptPlayerTurn(const Hand& hand, bool isPassOptionAvailable) override;
    void renderWinCondition(const std::string& winnerName) override;

    // --- Additional methods (Not part of GameRenderer public interface) ---
    void displayMessage(const std::string& message);
    void renderGameEnd(int player1Score, int player2Score);
    void renderRoundStart(int round);
    void renderTurnStart(const std::string& playerName);
};

#endif // GAMERENDERERCONSOLE_H
