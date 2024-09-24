# ⛴️ Ships Game

## 📜 Description

"Ships Game" is a simple naval combat game that allows players to compete against each other. Coded in C++, the game features a terminal interface to display the battlefield.

## 📝 Note

This game was initially developed by a team of three students. After receiving their final grades, two members decided to step away from the project. The game was then moved from the university's GitLab platform to this personal GitHub repository. Since that migration, all the work has been done by me, and other students have waived their rights to the project. I chose to continue developing it during the summer on my own.

## ✅ Requirements

Game requires C++ 20 or newer.

## 💾 Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/MaciejCieslik1/ShipsGame.git
    ```

2. Navigate to the project **ShipsGame** directory:
    ```sh
    cd ShipsGame/
    ```

3. Compile the project:
    ```sh
    make
    ```

4. Run the game:
    ```sh
    ./program
    ```
    
## 🎯 Game Preparation

1. **Start**: Allows you to go deeper into game preparation settings.

2. **New Game**: Allows the player to start a new game using hardcoded game parameters. The user must provide the players' names and select a board size from the range of <10, 30>.
   
3. **Load Game**: Allows the player to load the game state from a file, which includes all game parameters such as players' names, board size, ships, and islands.

## ℹ️ Game Rules

In "Ships Game" 2 players compete to destroy oponent's ships. Every ship is armed with rockets, which are used to attack other ships.

1. **Field and Board**
Each field has X and Y coordinate, which are greater than 0 and lower or equal to maximum board size. All fields are squares as is the board. Board size ranges from 10 to 30.

2. **Ships**:
In game there are 4 types of ships with different values of health points, size, movement and they carry different rockets. All ships are on the board in a horizontal position, meaning all squares have the same Y coordinate.
If ship has multiple sqaures, they must be connected as if they formed a rectangle. Ships have also names, described as one chracter. It is recommended to use different capital letters to name firt player's ships and to use
different small letters to name second player's ships. The ship is displayed on the baord by putting it's name letter on every field, which is occupied by this ship.

    **Battleship**:
      - Size: 4 fields
      - Health points: 10
      - Movement: 4
      - Missiles ID's: 0, 1, 2, 3
   
   **Cruiser**:
      - Size: 3 fields
      - Health points: 8
      - Movement: 6
      - Missiles ID's: 0, 1, 2

   **Destroyer**:
      - Size: 2 fields
      - Health points: 6
      - Movement: 8
      - Missiles ID's: 0, 1

   **Submarine**:
      - Size: 1 field
      - Health points: 4
      - Movement: 10
      - Missiles ID's: 0
  
4. **Islands**
The game provides also islands. Islands are displayed similarly to ships by instead of name letter in the field, the height is displayed. 






















