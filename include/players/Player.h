/**
 * @file Player.h
 * @brief Defines the abstract base class Player.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Card;
class Hand;
class Deck;

/**
 * @brief Abstract base class for all player types (Human, AI).
 *
 * Manages player state such as name, hand, deck, and passed status.
 */
class Player {
private:
    std::string name; ///< Player's name.
    std::unique_ptr<Hand> hand; ///< Player's hand.
    std::unique_ptr<Deck> deck; ///< Player's deck.
    bool hasPassed; ///< Flag indicating if the player has passed.

public:
    /**
     * @brief Constructor.
     * @param playerName The player's name.
     * @param playerDeck The deck associated with the player.
     * @param playerHand The hand associated with the player.
     */
    Player(const std::string& playerName, std::unique_ptr<Deck> playerDeck, std::unique_ptr<Hand> playerHand);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Player() = default;

    /**
     * @brief Pure virtual method for selecting a card (implemented in HumanPlayer/AIPlayer).
     * @return The card the player wants to play, or nullptr if the player passes/cannot play.
     */
    virtual std::shared_ptr<const Card> chooseCardToPlay() = 0;

    /**
     * @brief Pure virtual method for deciding whether to pass.
     * @return true if the player decides to pass, false otherwise.
     */
    virtual bool decideIfPass() = 0;

    /**
     * @brief Allows the player to replace cards.
     * @param cardsToReplace List of cards from the hand to be replaced.
     */
    void replaceCards(const std::vector<std::shared_ptr<const Card>>& cardsToReplace);

    /**
     * @brief Declares that the player is passing.
     */
    void pass();

    /**
     * @brief Automatically passes the player if they have no cards left.
     * @return true if the player automatically passed, false otherwise.
     */
    bool autoPassIfNoCards();

    /**
     * @brief Returns the player's pass status.
     * @return true if the player has passed, false otherwise.
     */
    bool getHasPassed() const
    { 
        return hasPassed; 
    }

    /**
     * @brief Returns a constant reference to the player's hand.
     * @return Constant reference to the Hand object.
     */
        // Read-only
    const Hand& getHand() const 
    { 
    return *hand;
    } 
    
    /**
     * @brief Returns a non-constant reference to the player's hand.
     * @return Non-constant reference to the Hand object.
     */
        // Read/write (for removeCard)
    Hand& getHand() 
    { 
    return *hand; 
    } 

    /**
     * @brief Returns a constant reference to the player's deck.
     * @return Constant reference to the Deck object.
     */
    const Deck& getDeck() const
    { 
        return *deck; 
    }

    /**
     * @brief Returns the player's name.
     * @return The player's name string.
     */
    const std::string& getName() const
    { 
        return name; 
    }
};

#endif // PLAYER_H
