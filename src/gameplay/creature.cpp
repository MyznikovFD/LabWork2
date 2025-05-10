#include "special_ability.h"


int creature::get_active_force() {
    int act_force = active_force;
    return act_force;
};

void creature::set_active_force(int new_force) {
    active_force = new_force;
};

