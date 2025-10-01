#include "ClearSky.h"
#include "GameField.h"

/**
 * @brief Applies the ClearSky effect to the game field.
 * @param field The game field.
 */
void ClearSky::applyEffect(GameField& field) const {
    // ClearSky effect: remove BitingFrost effect only.
    field.clearWeatherEffects();
}
