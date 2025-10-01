# System Requirements and Use Cases (Final Version)

## English Version

### System Requirements

#### Functional Requirements
1. **Game Mode Selection**
   - The system shall provide a menu for selecting game mode: Human vs Human or Human vs AI
   - The system shall initialize the appropriate player types based on selected mode

2. **Game Initialization**
   - The system shall create two identical decks of 11 unique cards for each player
   - The system shall deal 7 random cards to each player at game start
   - The system shall allow each player to replace up to 2 cards with different random cards from their deck

3. **Game Flow**
   - The system shall enforce turn-based gameplay between two human players or human and AI player
   - The system shall allow players to either play a card or pass on their turn
   - The system shall prevent players who have passed from playing additional cards
   - The system shall automatically mark a player as passed when they have no cards left
   - The system shall end the round when both players have passed

4. **Card Effects**
   - The system shall apply CommanderHorn effect: double the strength of all creatures
   - The system shall apply BitingFrost effect: set strength of all creatures to 1
   - The system shall apply ClearSky effect: remove BitingFrost effect
   - The system shall handle effect combination: CommanderHorn + BitingFrost = strength 2 for all creatures

5. **Victory Condition**
   - The system shall calculate final scores considering active effects
   - The system shall declare the player with higher total strength as winner

6. **Card Immutability**
   - All card classes shall be immutable after creation
   - Card properties (name, baseStrength) shall not be modifiable after object construction
   - Card objects shall be reusable across multiple game sessions
   - Card effects shall be applied through new object creation or external state management

### Use Cases

#### Use Case 0: Select Game Mode
**Actor:** Human Player
**Preconditions:** Application started
**Main Flow:**
1. System displays game mode selection menu
2. Player selects between "Human vs Human" and "Human vs AI"
3. System initializes the game with selected mode
4. System proceeds to initial card replacement phase

#### Use Case 1: Initial Card Replacement
**Actor:** Human Player (both players in Human vs Human mode)
**Preconditions:** Game mode selected, game has started, player has 7 cards
**Main Flow:**
1. System displays hand of 7 cards
2. Player selects up to 2 cards to replace
3. System removes selected cards from player's hand
4. System adds different random cards from deck to player's hand
5. System continues to main game phase

**Alternative Flow:**
- Player chooses to replace 0 cards → proceed directly to main game phase

#### Use Case 2: Play Creature Card
**Actor:** Current Player (Human or AI)
**Preconditions:** Player's turn, player has not passed, hand contains cards
**Main Flow:**
1. Player selects creature card from hand
2. System moves card from hand to game field
3. System recalculates current scores
4. System passes turn to next player

**Postconditions:** Card is on field, scores updated, turn changed

#### Use Case 3: Play Spell Card
**Actor:** Current Player (Human or AI)
**Preconditions:** Player's turn, player has not passed, hand contains spell card
**Main Flow:**
1. Player selects spell card from hand
2. System applies spell effect according to rules
3. System removes card from hand
4. System recalculates current scores
5. System passes turn to next player

#### Use Case 4: Player Pass
**Actor:** Current Player (Human or AI)
**Preconditions:** Player's turn, player has not passed
**Main Flow:**
1. Player selects pass option
2. System marks player as having passed
3. System passes turn to other player
4. If both players have passed, system proceeds to end game

#### Use Case 5: AI Turn
**Actor:** AI Player
**Preconditions:** AI player's turn, AI has not passed
**Main Flow:**
1. System evaluates game state
2. AI decides to play card or pass based on strategy
3. If playing card, system automatically plays selected card
4. If passing, system marks AI as having passed
5. System updates game state and passes turn

#### Use Case 6: Player Runs Out of Cards
**Actor:** Current Player (Human or AI)
**Preconditions:** Player's turn, player has no cards in hand, player has not passed
**Main Flow:**
1. System automatically marks player as having passed
2. System passes turn to other player
3. If both players have passed, system proceeds to end game
