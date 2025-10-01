# Simplified Gwent Project Architecture

## Overview
A simplified card game for two players with single round. Supports two game modes: Human vs Human and Human vs AI. Players can voluntarily stop playing cards before playing all cards in their hand.

## Deck Composition
Each player has an identical deck of 11 unique cards:

### **Creatures (8 cards)**
- CroneWhispess - strength 6
- CroneWeavess - strength 6  
- CroneBrewess - strength 6
- Catapult - strength 8
- SiegeExpert - strength 6
- BlueStripesCommando - strength 4
- CloseCombat - strength 5
- Archer - strength 4

### **Spells (3 cards)**
- CommanderHorn - doubles creature strength
- BitingFrost - sets all creature strength to 1
- ClearSky - removes BitingFrost effect

## Game Flow

### **Initial Phase**
1. Each player receives 7 random cards from their deck
2. Players can replace up to 2 cards:
   - Return selected cards to the deck
   - Receive **different random cards from the deck** (not the same ones)

### **Main Phase**
- Players take turns playing one card at a time
- Player can declare pass on their turn
- After declaring pass, player cannot play more cards this round
- If player has no cards left, they are automatically considered passed
- Round ends when both players have passed

### **Completion**
- Score calculation considering active effects
- Player with higher total strength wins

## Class Responsibilities by Package

### **Core Package**
- **GameMenu** - manages game mode selection and main menu
- **Game** - manages game flow, tracks player pass states and game mode
- **GameField** - calculates current scores considering active effects

### **Players Package**
- **Player** - base class with pass state management
- **HumanPlayer** - handles human input for card selection and passing
- **AIPlayer** - contains AI logic for card selection and pass decisions

### **Cards Package**
All cards store only base strength. Effects are calculated dynamically during score calculation.

### **Utilities Package**
- **Deck** - manages deck operations and card replacement
- **Hand** - manages player's hand cards

### **Display Package**
- **GameRenderer** - renders game interface, menu, and game state

## Effect Logic
- **CommanderHorn**: creature strength doubles
- **BitingFrost**: all creature strength set to 1
- **CommanderHorn + BitingFrost**: all creature strength set to 2
- **ClearSky**: cancels BitingFrost effect only

## Pass Strategy
- **HumanPlayer**: can voluntarily declare pass through interface
- **AIPlayer**: makes pass decision based on game state analysis
- **Automatic**: player automatically passes when no cards remain
