@startuml

package Core {
  class GameMenu {
    -Game game
    +void showMainMenu()
    +void selectGameMode(GameMode mode)
    +void startGame()
  }

  class Game {
    -Player player1
    -Player player2
    -GameField field
    -boolean gameActive
    -GameMode currentMode
    +void startGame()
    +void endTurn()
    +void checkWinCondition()
    +void processCardReplacement()
    +void setGameMode(GameMode mode)
  }

  class GameField {
    -List<Card> player1Cards
    -List<Card> player2Cards
    -boolean commanderHornActive
    -boolean bitingFrostActive
    +void calculateScores()
    +void clearWeatherEffects()
    +int getPlayer1Score()
    +int getPlayer2Score()
  }
}

package Players {
  abstract class Player {
    #String name
    #Hand hand
    #Deck deck
    #boolean hasPassed
    +void drawCard()
    +void playCard(Card card)
    +void pass()
    +void autoPassIfNoCards()
    +void replaceCards(List<Card> cardsToReplace)
    +boolean hasPassed()
  }
  
  class HumanPlayer {
    +void selectCard()
    +void decidePass()
  }
  
  class AIPlayer {
    +Card chooseCardToPlay()
    +boolean decideIfPass()
    +List<Card> chooseCardsToReplace()
  }
}

package Cards {
  abstract class Card {
    -String name
    -int baseStrength
    +void play(GameField field)
    +String getName()
    +int getBaseStrength()
  }
  
  package Creatures {
    class CroneWhispess
    class CroneWeavess
    class CroneBrewess
    class Catapult
    class SiegeExpert
    class BlueStripesCommando
    class CloseCombat
    class Archer
  }
  
  package Spells {
    class CommanderHorn
    class BitingFrost
    class ClearSky
  }
}

package Utilities {
  class Deck {
    -List<Card> cards
    +void shuffle()
    +Card drawCard()
    +void initializeDeck()
    +List<Card> drawDifferentCards(int count, List<Card> excluded)
  }
  
  class Hand {
    -List<Card> cards
    +void addCard(Card card)
    +void removeCard(Card card)
    +List<Card> getCards()
    +int getSize()
  }
}

package Display {
  class GameRenderer {
    +void renderMainMenu()
    +void renderGameModeSelection()
    +void renderGameField(GameField field)
    +void renderHand(Hand hand, boolean isHuman)
    +void renderScores(int player1Score, int player2Score)
    +void renderPassStatus(boolean humanPassed, boolean aiPassed)
    +void renderCardReplacementInterface(Hand hand)
  }
}

enum GameMode {
  HUMAN_VS_HUMAN
  HUMAN_VS_AI
}

Player <|-- HumanPlayer
Player <|-- AIPlayer

Card <|-- CroneWhispess
Card <|-- CroneWeavess
Card <|-- CroneBrewess
Card <|-- Catapult
Card <|-- SiegeExpert
Card <|-- BlueStripesCommando
Card <|-- CloseCombat
Card <|-- Archer
Card <|-- CommanderHorn
Card <|-- BitingFrost
Card <|-- ClearSky

GameMenu --> Game : creates
Game *-- Player
Game *-- GameField
Player *-- Hand
Player *-- Deck
GameField o-- Card
Deck o-- Card
Hand o-- Card

Game --> GameRenderer : uses
GameRenderer --> GameMenu : displays
AIPlayer --> Card : chooses
HumanPlayer --> Card : selects
GameMenu --> GameMode : uses
Game --> GameMode : has
@enduml
