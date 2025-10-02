#include "AIPlayer.h"
#include "Deck.h"
#include "Hand.h"
#include <algorithm>
#include <map>
#include <random>
#include <ctime>
#include <utility>

/**
 * @brief Constructor.
 * @param playerName The player's name.
 * @param playerDeck The player's deck.
 * @param playerHand The player's hand.
 * @param renderer The game renderer.
 */
AIPlayer::AIPlayer(const std::string& playerName, std::unique_ptr<Deck> playerDeck, std::unique_ptr<Hand> playerHand, std::shared_ptr<GameRenderer> gameRenderer)
    : Player(playerName, std::move(playerDeck), std::move(playerHand)), renderer(std::move(gameRenderer))
{
}

/**
 * @brief Selects a card to play based on AI strategy.
 * @return The card selected by the AI, or nullptr if the AI passes.
 */
std::shared_ptr<const Card> AIPlayer::chooseCardToPlay() {
    // STUB: Plays all cards in arbitrary (random) order until hand is empty.
    const auto& cards = getHand().getCards();
    if (!cards.empty()) {
        unsigned seed = static_cast<unsigned>(std::time(0));
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<size_t> distribution(0, cards.size() - 1);
        size_t index = distribution(rng);
        return cards[index];
    }
    return nullptr;
}

/**
 * @brief Decision to pass on the turn.
 * @return true if the AI decides to pass, false otherwise.
 */
bool AIPlayer::decideIfPass() {
    // If chooseCardToPlay returns nullptr (hand empty), the AI automatically passes.
    // If not, it means a card was played, so the AI does not pass yet.
    return getHasPassed();
}

/**
 * @brief Selects cards for replacement based on AI strategy.
 * @return A list of cards selected by the AI for replacement (up to 2).
 */
std::vector<std::shared_ptr<const Card>> AIPlayer::chooseCardsToReplace() const {
    std::vector<std::shared_ptr<const Card>> cardsToReplace;
    const auto& cards = getHand().getCards();
    
    // Categorize cards
    std::vector<std::shared_ptr<const Card>> creatures;
    std::vector<std::shared_ptr<const Card>> spells;
    std::map<std::string, std::shared_ptr<const Card>> spellMap;
    std::vector<std::shared_ptr<const Card>> weakCreatures; // Strength 4 or 5

    for (const auto& card : cards) {
        if (card->isSpell()) {
            spells.push_back(card);
            spellMap[card->getName()] = card;
        } else {
            creatures.push_back(card);
            if (card->getBaseStrength() == 4 || card->getBaseStrength() == 5) {
                weakCreatures.push_back(card);
            }
        }
    }
    
    size_t C = creatures.size(); // Creatures in Hand
    size_t S = spells.size();    // Spells in Hand

    // Helper to find and add the weakest creature
    auto findWeakestCreature = [&]() -> std::shared_ptr<const Card> {
        if (creatures.empty()) return nullptr;
        return *std::min_element(creatures.begin(), creatures.end(), 
            [](const auto& a, const auto& b) {
                return a->getBaseStrength() < b->getBaseStrength();
            });
    };

    // --- Strategy Implementation ---

    // 1. C=4 (S=3: All spells are in hand) -> Replace ClearSky and BitingFrost.
    if (C == 4 && spellMap.count("ClearSky") && spellMap.count("BitingFrost")) {
        cardsToReplace.push_back(spellMap.at("ClearSky"));
        cardsToReplace.push_back(spellMap.at("BitingFrost"));
    } 
    // 2. C=5 (S=2: 2 spells are in hand) -> Replace 2 spell cards.
    else if (C == 5 && S >= 2) {
        // Replace the first two found spells
        cardsToReplace.insert(cardsToReplace.end(), spells.begin(), spells.begin() + 2);
    }
    // 3. C=6 (S=1: 1 spell is in hand) -> Replace cards with strength 4 and 5 OR 1 spell.
    else if (C == 6) {
        // Option 1: Replace creatures with strength 4 and 5
        if (weakCreatures.size() >= 2) {
            cardsToReplace.push_back(weakCreatures[0]);
            cardsToReplace.push_back(weakCreatures[1]);
        } 
        // Option 2: Replace 1 spell
        else if (!spells.empty()) {
             cardsToReplace.push_back(spells[0]);
        }
    }
    // 4. C=7 (S=0: No spells in hand) -> Replace weakest creature.
    else if (C == 7) {
        std::shared_ptr<const Card> weakest = findWeakestCreature();
        if (weakest) {
            cardsToReplace.push_back(weakest);
        }
    }
    // 5. Special Spell Combination Rules (applied only if no general rule was met)
    else {
        // CH & CS in hand: Replace cards with strength 4 and 5 OR replace nothing.
        if (spellMap.count("CommanderHorn") && spellMap.count("ClearSky")) {
            if (weakCreatures.size() >= 2) {
                 cardsToReplace.push_back(weakCreatures[0]);
                 cardsToReplace.push_back(weakCreatures[1]);
            }
            // Else, replace nothing (cardsToReplace remains empty)
        }
        // CH & BF in hand: Replace BitingFrost.
        else if (spellMap.count("CommanderHorn") && spellMap.count("BitingFrost")) {
            cardsToReplace.push_back(spellMap.at("BitingFrost"));
        }
    }

    // Ensure we don't replace more than 2 cards
    if (cardsToReplace.size() > 2) {
        cardsToReplace.resize(2);
    }
    
    return cardsToReplace;
}
