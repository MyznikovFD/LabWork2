#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include <vector>
#include <string>
#include "deck.h"
#include "line_spell.h"
#include "creature.h"

/// The game field 
/*! If a card is put in one of lines, the card is active.
In the end of rounds and all the game it defines the winner 
*/ 
class Game_field {
    Deck dump_player0;
    Deck dump_player1;

    std::vector<Creature*> shortrange_player0;
    std::vector<Creature*> longrange_player0;
    
    std::vector<Line_spell*> shortrange_spells_player0;
    std::vector<Line_spell*> longrange_spells_player0;

    
    std::vector<Creature*> shortrange_player1;
    std::vector<Creature*> longrange_player1;

    std::vector<Line_spell*> shortrange_spells_player1;
    std::vector<Line_spell*> longrange_spells_player1;


    int strength_player0;
    int strength_player1;

    counter_loses0 = 0;
    counter_loses1 = 0;


    ///The method removes cards from 1 line
    void clean_line(std::vector<Creature*> line);
    
    
public:
    /// The method defines the winner of all the game 
    std::string define_game_winner();
    
    /// The method increases counter of loses for that who did not win in the round
    void define_round_winner();


    /// The method calculates strengths of players' armies
    void caluclate_strenghts();


    /// The method returns vector with id of cards which are in shorttrange_line 
    std::vector<int> enum_shortrange_line();
    
    /// The method returns vector with id of cards which are in longrange_line
    std::vector<int> enum_longrange_line();


    ///The method removes cards from all the lines
    void cleanall();

#endif
