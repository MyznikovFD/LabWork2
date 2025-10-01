#include "GameField.h"

/**
 * @brief Default constructor.
 */
GameField::GameField()
    : commanderHornActive(false), bitingFrostActive(false)
{
}

/**
 * @brief Adds a played card to the field.
 * @param card The card to add.
 * @param isPlayer1 Flag indicating if the card was played by Player 1.
 */
void GameField::addCard(std::shared_ptr<const Card> card, bool isPlayer1) {
    // Based on simplified Gwent, only creature cards stay on the field.
    if (!card->isSpell()) {
        if (isPlayer1) {
            player1Cards.push_back(std::move(card));
        } else {
            player2Cards.push_back(std::move(card));
        }
    }
}

/**
 * @brief Sets the activity status of the CommanderHorn effect.
 * @param active The new activity state.
 */
void GameField::setCommanderHornActive(bool active) {
    commanderHornActive = active;
}

/**
 * @brief Sets the activity status of the BitingFrost effect.
 * @param active The new activity state.
 */
void GameField::setBitingFrostActive(bool active) {
    bitingFrostActive = active;
}

/**
 * @brief Clears weather effects (specifically BitingFrost).
 */
void GameField::clearWeatherEffects() {
    // Requirements state ClearSky removes BitingFrost only.
    bitingFrostActive = false;
}

/**
 * @brief Calculates the effective strength of a single card considering active effects.
 * @param card The card to calculate strength for.
 * @return The card's current effective strength.
 */
int GameField::calculateCardStrength(const std::shared_ptr<const Card>& card) const {
    // Only creature cards contribute to the score.
    if (card->isSpell()) {
        return 0;
    }

    int strength = card->getBaseStrength();

    // 1. Apply BitingFrost effect (set strength to 1)
    if (bitingFrostActive) {
        strength = 1;
    }

    // 2. Apply CommanderHorn effect (double strength)
    if (commanderHornActive) {
        strength *= 2;
    }

    return strength;
}

/**
 * @brief Calculates Player 1's total score considering active effects.
 * @return Player 1's total score.
 */
int GameField::getPlayer1Score() const {
    int totalScore = 0;
    for (const auto& card : player1Cards) {
        totalScore += calculateCardStrength(card);
    }
    return totalScore;
}

/**
 * @brief Calculates Player 2's total score considering active effects.
 * @return Player 2's total score.
 */
int GameField::getPlayer2Score() const {
    int totalScore = 0;
    for (const auto& card : player2Cards) {
        totalScore += calculateCardStrength(card);
    }
    return totalScore;
}
