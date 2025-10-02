#include "HumanPlayer.h"
#include "Deck.h"
#include "Hand.h"

/**
 * @brief Constructor.
 * @param playerName The player's name.
 * @param playerDeck The player's deck.
 * @param playerHand The player's hand.
 * @param renderer The game renderer for I/O.
 */
HumanPlayer::HumanPlayer(const std::string& playerName, std::unique_ptr<Deck> playerDeck, std::unique_ptr<Hand> playerHand, std::shared_ptr<GameRenderer> gameRenderer)
    : Player(playerName, std::move(playerDeck), std::move(playerHand)), renderer(std::move(gameRenderer))
{
}

/**
 * @brief Selects a card to play (requires user input via renderer).
 * @return The card selected by the user, or nullptr if the user passes.
 */
std::shared_ptr<const Card> HumanPlayer::chooseCardToPlay() {
    // Pass the 'hasPassed' status to the renderer for correct prompting.
    bool isPassOptionAvailable = !getHasPassed(); 
    return renderer->promptPlayerTurn(getHand(), isPassOptionAvailable);
}

/**
 * @brief Decision to pass. Handled by chooseCardToPlay returning nullptr.
 * @return true if the player has passed, false otherwise.
 */
bool HumanPlayer::decideIfPass() {
    return getHasPassed();
}

/**
 * @brief Selects cards for replacement (requires user input via renderer).
 * @return A list of cards selected for replacement.
 */
std::vector<std::shared_ptr<const Card>> HumanPlayer::selectCardsToReplace() const {
    return renderer->renderCardReplacementInterface(getHand());
}
