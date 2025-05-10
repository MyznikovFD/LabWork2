#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include <vector>
#include "deck.h"
#include "line_spell.h"
#include "creature.h"

/// The game field 
/*! If a card is put in one of lines, it is active.
In the end of rounds0 and all the game it defines the winner 
*/ 
class Game_field {
    Deck dump_player0;
    Deck dump_player1;

    vector<Creature*> shortrange_player0;
    vector<Creature*> longrange_player0;
    
    vector<Line_spell> shortrange_spells_player0;
    vector<Line_spell> longrange_spells_player0;

    
    vector<Creature*> shortrange_player1;
    vector<Creature*> longrange_player1;

    vector<Line_spell> shortrange_spells_player1;
    vector<Line_spell> longrange_spells_player1;


    int strength_player0;
    int strength_player1;

    counter_loses0;
    counter_lose1;


    /// The method returns vector with id of cards which are in shorttrange_line 
    vector<int> enum_shortrange_line();
    
    /// The method returns vector with id of cards which are in longrange_line
    vector<int> enum_longrange_line();
    
    ///The method removes cards from 1 line
    void clean_line(vector<Creature*> line);
    
    
public:
    /// The method defines the winner of round and all the game 
    /*! The method increases counter of loses, and makes the player losed 2 times losed in the game.
 */ 
    void define_winner();


    /// The method calculates strengths of players' armies
    void caluclate_streghts();


    ///The method assignes strengths of players' armies
    void enum();


    ///The method removes cards from all the lines
    void cleanall();

#endif
