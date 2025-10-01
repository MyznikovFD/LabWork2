#include "BitingFrost.h"
#include "GameField.h"

/**
 * @brief Applies the BitingFrost effect to the game field.
 * @param field The game field.
 */
void BitingFrost::applyEffect(GameField& field) const {
    // BitingFrost effect: set strength of all creatures to 1.
    field.setBitingFrostActive(true);
}
