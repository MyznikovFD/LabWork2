#include "CommanderHorn.h"
#include "GameField.h"

/**
 * @brief Applies the CommanderHorn effect to the game field.
 * @param field The game field.
 */
void CommanderHorn::applyEffect(GameField& field) const {
    // CommanderHorn effect: double the strength of all creatures.
    field.setCommanderHornActive(true);
}
