#include "GameRendererConsole.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include "CreatureCard.h"

/**
 * @brief Centralized function for getting string input from console.
 *
 * Removes const because std::cin is a global stream and its state
 * changes when reading. This is the core for all user input.
 * * @return Input string.
 */
std::string GameRendererConsole::getInput() {
    std::string input;
    // Use std::getline for reliable reading of the entire line
    std::getline(std::cin, input);
    
    // Convert input to lowercase for easier command parsing
    std::transform(input.begin(), input.end(), input.begin(),
        [](unsigned char c){ return std::tolower(c); });
    
    return input;
}

/**
 * @brief Helper function for rendering card in pseudographics.
 */
std::vector<std::string> GameRendererConsole::renderCardBox(const std::shared_ptr<const Card>& card, int index, bool showIndex) const {
    // Temporarily keep the implementation from the original snippet, assuming it works
    if (!card) {
        return {"+------+", "| **** |", "| **** |", "| **** |", "|      |", "+------+"};
    }

    std::string name = card->getName();
    std::string s_str;

    if (auto creatureCard = std::dynamic_pointer_cast<const CreatureCard>(card)) {
        s_str = "S:" + std::to_string(creatureCard->getBaseStrength());
    } else if (card->isSpell()) {
        s_str = "Spell";
    } else {
        s_str = "Card"; // Fallback for safety
    }

    // Truncate name to fit in the frame
    std::string name_part1 = name.substr(0, std::min(name.length(), (size_t)4));
    std::string name_part2 = (name.length() > 4) ? name.substr(4, 4) : "";

    // Форматируем части имени и s_str для ширины 4
    std::stringstream ss1, ss2, ss_str_ss;

    ss1 << std::left << std::setw(4) << name_part1;
    name_part1 = ss1.str();

    ss2 << std::left << std::setw(4) << name_part2;
    name_part2 = ss2.str();

    ss_str_ss << std::left << std::setw(4) << s_str;
    s_str = ss_str_ss.str();
    
    std::vector<std::string> box = {
        "+------+",
        "| " + name_part1 + " |",
        "| " + name_part2 + " |",
        "| " + s_str + " |",
        "|      |",
        "+------+"
    };
    
    if (showIndex && index > 0) {
        std::string indexStr = std::to_string(index);
        box[0][1] = indexStr[0];
        if (indexStr.length() > 1) {
             box[0][2] = indexStr[1];
        }
    }
    
    return box;
}

void GameRendererConsole::renderMainMenu() {
    // Display menu
    std::cout << "\n\n--- GWENT: SIMPLIFIED EDITION ---\n"
              << "1. Human vs Human\n"
              << "2. Human vs AI\n"
              << "3. Exit\n"
              << "Enter choice: ";
}

/**
 * @brief Gets game mode selection.
 *
 * Uses getInput() for reading, following SRP.
 */
GameMode GameRendererConsole::renderGameModeSelection() {
    renderMainMenu(); // Redisplay if needed
    std::string input = getInput();
    
    try {
        int choice = std::stoi(input);
        switch (choice) {
            case 1: return GameMode::HUMAN_VS_HUMAN;
            case 2: return GameMode::HUMAN_VS_AI;
            case 3: 
                displayMessage("Exiting...");
                exit(0);
            default:
                displayMessage("Invalid choice, defaulting to Human vs AI");
                return GameMode::HUMAN_VS_AI;
        }
    } catch (const std::exception&) {
        displayMessage("Invalid input, defaulting to Human vs AI");
        return GameMode::HUMAN_VS_AI;
    }
}

void GameRendererConsole::renderGameField(const GameField& field) {
    std::cout << "\n========================================\n";
    std::cout << "           GWENT GAME FIELD\n";
    std::cout << "========================================\n";

    // --- Player 2 (AI/Opponent) Cards ---
    std::cout << "\n--- Opponent's Cards (" << field.getPlayer2Cards().size() << " cards) ---\n";
    const auto& cards2 = field.getPlayer2Cards();
    if (cards2.empty()) {
        std::cout << "No cards played.\n";
    } else {
        // Render player 2 cards
        std::vector<std::vector<std::string>> cardBoxes2;
        for (const auto& card : cards2) {
            // Index 0 for field cards, showIndex=false
            cardBoxes2.push_back(renderCardBox(card, 0, false));
        }
        
        // Output line by line
        if (!cardBoxes2.empty()) {
            for (size_t i = 0; i < cardBoxes2[0].size(); ++i) {
                for (const auto& box : cardBoxes2) {
                    std::cout << box[i] << "  ";
                }
                std::cout << "\n";
            }
        }
    }

    // --- Weather/Effect Status ---
    std::cout << "\n--- Current Effects ---\n";
    std::cout << "  Commander Horn: " << (field.isCommanderHornActive() ? "ACTIVE" : "Inactive") << "\n";
    std::cout << "  Biting Frost:   " << (field.isBitingFrostActive() ? "ACTIVE (Strength 1)" : "Inactive") << "\n";
    
    // --- Player 1 (Human) Cards ---
    std::cout << "\n--- Your Cards (" << field.getPlayer1Cards().size() << " cards) ---\n";
    const auto& cards1 = field.getPlayer1Cards();
    if (cards1.empty()) {
        std::cout << "No cards played.\n";
    } else {
        // Render player 1 cards
        std::vector<std::vector<std::string>> cardBoxes1;
        for (const auto& card : cards1) {
            cardBoxes1.push_back(renderCardBox(card, 0, false));
        }
        
        // Output line by line
        if (!cardBoxes1.empty()) {
            for (size_t i = 0; i < cardBoxes1[0].size(); ++i) {
                for (const auto& box : cardBoxes1) {
                    std::cout << box[i] << "  ";
                }
                std::cout << "\n";
            }
        }
    }
    std::cout << "========================================\n";
}

void GameRendererConsole::renderHand(const Hand& hand, bool isHuman) {
    if (!isHuman) {
        std::cout << "\n--- Opponent's Hand (" << hand.getSize() << " cards) ---\n";
        // For AI just show card count
        std::cout << "+-----------------+\n";
        std::cout << "| " << std::left << std::setw(15) << hand.getSize() << " cards | \n";
        std::cout << "+-----------------+\n";
        return;
    }

    std::cout << "\n--- Your Hand (" << hand.getSize() << " cards) ---\n";
    const auto& cards = hand.getCards();
    if (cards.empty()) {
        std::cout << "Hand is empty. You must pass.\n";
        return;
    }

    std::vector<std::vector<std::string>> cardBoxes;
    int index = 1;
    for (const auto& card : cards) {
        // showIndex=true, index > 0
        cardBoxes.push_back(renderCardBox(card, index++, true));
    }
    
    // Output line by line
    for (size_t i = 0; i < cardBoxes[0].size(); ++i) {
        for (const auto& box : cardBoxes) {
            std::cout << box[i] << "  ";
        }
        std::cout << "\n";
    }
}

void GameRendererConsole::renderScores(int player1Score, int player2Score) {
    std::cout << "\n*** SCORES ***\n";
    std::cout << "  Player 1 (You): " << player1Score << "\n";
    std::cout << "  Player 2 (Opponent): " << player2Score << "\n";
    std::cout << "**************\n";
}

void GameRendererConsole::renderPassStatus(bool player1Passed, bool player2Passed) {
    std::cout << "\n--- Pass Status ---\n";
    std::cout << "  Player 1 (You): " << (player1Passed ? "PASSED" : "Active") << "\n";
    std::cout << "  Player 2 (Opponent): " << (player2Passed ? "PASSED" : "Active") << "\n";
    std::cout << "-------------------\n";
}

/**
 * @brief Handles card replacement interface and gets user selection.
 */
std::vector<std::shared_ptr<const Card>> GameRendererConsole::renderCardReplacementInterface(const Hand& hand) {
    std::vector<std::shared_ptr<const Card>> cardsToReplace;
    int replacementCount = 0;

    displayMessage("Card Replacement Phase (Up to 2 cards)");
    renderHand(hand, true);
    
    std::cout << "Enter up to 2 card indices to replace (e.g., 1,3). Press Enter to skip.\n"
              << "Your choice: ";
    
    std::string input = getInput();

    if (input.empty()) {
        displayMessage("Skipping card replacement.");
        return cardsToReplace; // Empty list
    }

    std::stringstream ss(input);
    std::string segment;
    
    while (std::getline(ss, segment, ',') && replacementCount < 2) {
        try {
            // Remove spaces around segment
            segment.erase(0, segment.find_first_not_of(" \t\r\n"));
            segment.erase(segment.find_last_not_of(" \t\r\n") + 1);

            if (segment.empty()) continue;

            int index = std::stoi(segment);
            if (index >= 1 && index <= hand.getSize()) {
                // Cards in hand: [0] = index 1, [1] = index 2, etc.
                const auto& card = hand.getCards()[index - 1];
                
                // Check if card is already selected
                bool alreadySelected = false;
                for (const auto& c : cardsToReplace) {
                    if (c == card) {
                        alreadySelected = true;
                        break;
                    }
                }

                if (!alreadySelected) {
                    cardsToReplace.push_back(card);
                    replacementCount++;
                } else {
                    displayMessage("Card index " + std::to_string(index) + " already selected.");
                }
            } else {
                displayMessage("Invalid card index: " + std::to_string(index) + ". Must be between 1 and " + std::to_string(hand.getSize()));
            }
        } catch (const std::exception&) {
            displayMessage("Invalid input format detected in segment: " + segment);
        }
    }

    if (replacementCount > 0) {
        std::string cardNames;
        for (const auto& card : cardsToReplace) {
            cardNames += card->getName() + ", ";
        }
        displayMessage("Selected for replacement: " + cardNames.substr(0, cardNames.length() - 2));
    }

    return cardsToReplace;
}

/**
 * @brief Prompts player to choose a card or pass.
 *
 * Uses getInput() for command reading, following SRP.
 */
std::shared_ptr<const Card> GameRendererConsole::promptPlayerTurn(const Hand& hand, bool isPassOptionAvailable) {
    bool validChoice = false;
    std::shared_ptr<const Card> selected_card = nullptr;
    
    while (!validChoice) {
        renderHand(hand, true); // Display current hand
        
        std::cout << "\nEnter card index to play, 'pass' to pass, or 'help' for info: ";
        std::string input = getInput();

        if (input == "help") {
            renderHelp();
            continue;
        }

        if (input == "pass") {
            if (isPassOptionAvailable) {
                validChoice = true;
                selected_card = nullptr; // nullptr means "pass"
                displayMessage("You chose to pass this round.");
            } else {
                displayMessage("You have already passed and cannot perform any more actions.");
            }
            continue;
        }

        // Try to parse card index
        try {
            int index = std::stoi(input);
            if (index >= 1 && index <= hand.getSize()) {
                selected_card = hand.getCards()[index - 1];
                validChoice = true;
            } else {
                displayMessage("Invalid card index. Choose a number between 1 and " + std::to_string(hand.getSize()) + ".");
            }
        } catch (const std::exception&) {
            displayMessage("Invalid command. Enter a card index, 'pass', or 'help'.");
        }
    }
    
    return selected_card;
}

void GameRendererConsole::renderWinCondition(const std::string& winnerName) {
    if (winnerName == "Draw") {
        std::cout << "\n!!! THE ROUND ENDED IN A DRAW !!!\n";
    } else {
        std::cout << "\n!!! " << winnerName << " WINS THE ROUND !!!\n";
    }
}

void GameRendererConsole::displayMessage(const std::string& message) {
    std::cout << "\n[INFO] " << message << "\n";
}

void GameRendererConsole::renderGameEnd(int player1Score, int player2Score) {
    std::cout << "\n\n****************************************\n";
    std::cout << "            GAME OVER\n";
    std::cout << "****************************************\n";

    if (player1Score > player2Score) {
        std::cout << "PLAYER 1 WINS! (Final Score: " << player1Score << " vs " << player2Score << ")\n";
    } else if (player2Score > player1Score) {
        std::cout << "PLAYER 2 WINS! (Final Score: " << player2Score << " vs " << player1Score << ")\n";
    } else {
        std::cout << "IT'S A DRAW! (Final Score: " << player1Score << " vs " << player2Score << ")\n";
    }

    std::cout << "****************************************\n\n";
}

void GameRendererConsole::renderRoundStart(int round) {
    std::cout << "\n\n----------------------------------------\n"
              << "             ROUND " << round << " START\n"
              << "----------------------------------------\n";
}

void GameRendererConsole::renderTurnStart(const std::string& playerName) {
    std::cout << "\n>>> " << playerName << "'s turn <<<\n";
}

void GameRendererConsole::renderHelp() const {
    std::cout << "\n--- HELP ---\n"
              << "COMMANDS:\n"
              << "  [number]: Play the card at the specified index from your hand (e.g., '1', '3').\n"
              << "  pass: Pass your turn. You cannot play any more cards this round.\n"
              << "  help: Show this help message.\n\n"
              << "CARD EFFECTS:\n"
              << "  Creature Card: Base Strength (S) is added to your score.\n"
              << "  CommanderHorn: Doubles the strength of all creatures currently on the field.\n"
              << "  BitingFrost: Sets the strength of all creatures on the field to 1.\n"
              << "  ClearSky: Removes the BitingFrost effect (does NOT affect CommanderHorn).\n"
              << "----------------\n";
}
