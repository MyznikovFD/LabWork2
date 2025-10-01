@startuml

package Core {
  [GameMenu]
  [Game] 
  [GameField]
}

package Players {
  [HumanPlayer] 
  [AIPlayer]
}

package Cards {
  [Deck]
  [Hand]
  [Card]
}

package Display {
  [GameRenderer]
}

GameMenu --> Game : starts
Game --> HumanPlayer : manages
Game --> AIPlayer : manages
Game --> GameField : uses
Game --> Deck : uses
Game --> Hand : uses
Game --> GameRenderer : updates
GameRenderer --> GameMenu : displays
GameRenderer --> HumanPlayer : interacts
Hand --> Card : contains
Deck --> Card : contains
GameField --> Card : contains
@enduml
