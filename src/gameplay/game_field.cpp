#include <vector>
#include <string>
#include "deck.h"
#include "card.h"
#include "line_spell.h"
#include "creature.h"



void Game_field::calculate_strenghts() {
    int strenght_var = 0;
    for (int i = shortrange_player0.size() - 1, i > -1, i--) {
        strenght_var = strenght_var + shortrange_player0[i]->get_active_force();
    }

    for (int i = longrange_player0.size() - 1, i > -1, i--) {
        strenght_var = strenght_var + longrange_player0[i]->get_active_force();
    }
    strenght_player0 = strenght_var;
    
    strenght_var = 0;
    for (int i = shortrange_player1.size() - 1, i > -1, i--) {
        strenght_var = strenght_var + shortrange_player1[i]->get_active_force();
    }
    
    for (int i = longrange_player1.size() - 1, i > -1, i--) {
        strenght_var = strenght_var + longrange_player1[i]->get_active_force();
    }
    strenght_player1 = strenght_var;
};


void Game_field::define_round_winner() {
    if (strength_player0 == strength_player1) {
        counter_loses0++;
        counter_loses1++;
    }
    if (strength_player0 < strength_player1) {
        counter_loses0++;
    }
    if (strength_player0 > strength_player1) {
        counter_loses01++;
    } 
};


std:string Game_field::define_game_winner() {
    if ((strength_player0 == counter_loses1 and counter_loses0 == 2)) {
        return "draw";
    }
    if (counter_loses0 > 1) {
        return "1";
    }
    if (counter_loses1 > 1) {
        return "0";
    } 
};


std::vector<int> Game_field::enum_shortrange_line(int number_of_player) {
    std::vector<int> ids;
    std::vector<Creature*> creature_line;
    std::vector<Creature*> spell_line;
    if (number_of_player == 0) {
        creature_line = shortrange_player0;
        spell_line = shortrange_spells_player0;
    } else {
        line = shortrange_player1;
        spell_line = shortrange_spells_player1;
    }
    for (int i = creature_line.size() - 1, i > -1, i--) {
        ids.push_back(creature_line[i]->get_id());
    }
    for (int i = spell_line.size() - 1, i > -1, i--) {
        ids.push_back(spell_line[i]->get_id());
    }
    return ids;
};
std::vector<int> Game_field::enum_longrange_line(int number_of_player) {
    std::vector<int> ids;
    std::vector<Creature*> creature_line;
    std::vector<Creature*> spell_line;
    if (number_of_player == 0) {
        creature_line = longrange_player0;
        spell_line = longrange_spells_player0;
    } else {
        line = longrange_player1;
        spell_line = longrange_spells_player1;
    }
    for (int i = creature_line.size() - 1, i > -1, i--) {
        ids.push_back(creature_line[i]->get_id());
    }
    for (int i = spell_line.size() - 1, i > -1, i--) {
        ids.push_back(spell_line[i]->get_id());
    }
    return ids;
};



void Game_field::clean_line(std::vector<Creature*> line) {
    
    for (int i = line.size() - 1, i > -1, i--) {
        if (line[i].get_side_battle == 0) { 
            dump0.put_in(line[i]); 
        } else {
            dump1.put_in(line[i]);
        } 
    }
};

void Game_field::cleanall() {
    
    clean_line(shortrange_player0);
    clean_line(longrange_player0);

    shortrange_spells_player0.clear();
    longrange_spells_player0.clear();

    clean_line(shortrange_player1);
    clean_line(longrange_player1);

    shortrange_spells_player1.clear();
    longrange_spells_player1.clear();
};

