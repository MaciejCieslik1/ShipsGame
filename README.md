# ⛴️ Ships Game

## 📜 Description

"Ships Game" is a simple naval combat game that allows players to compete against each other. Coded in C++, the game features a terminal interface to display the battlefield.

## 📝 Note

This game was initially developed by a team of three students. After receiving their final grades, two members decided to step away from the project. The game was then moved from the university's GitLab platform to this personal GitHub repository. Since that migration, all the work has been done by me, and other students have waived their rights to the project. I chose to continue developing it during the summer.

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

2. **Languages**: There are 10 languages avalaible.

3. **New Game**: Allows the player to start a new game using hardcoded game parameters. The user must provide the players' names and select a board size from the range of <10, 30>.
   
4. **Load Game**: Allows the player to load the game state from a file, which includes all game parameters such as players' names, board size, ships, and islands.

## ℹ️ Game Rules

In "Ships Game" 2 players compete to destroy oponent's ships. Every ship is armed with rockets, which are used to attack other ships.

1. **Field and Board**:
Each field has X and Y coordinate, which are greater than 0 and lower or equal to maximum board size. All fields are squares as is the board. Board size ranges from 10 to 30.

2. **Ships**:
In game there are 4 types of ships with different values of health points, size, coordinates, movement and they carry different rockets. All ships are on the board in a horizontal position, meaning all squares have the same Y coordinate.
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
  
4. **Islands**:
The game provides also islands. Islands are displayed similarly to ships, but instead of name letter in the field, the height is displayed. Each island has height and coordinates.
In contrast to ships, the fields occupied by islands do not have to be adjacent.

5. **Missiles**:
Every ship carries rockets. Each rocket has damage, range, altitude and ID. If the rocket hits the field on which there is a ship, damage is dealt. The path of the rocket is calculated, using linuar function and if there is a island on the rocket's way and it's heigth is bigger or equal to rocket's altitude the rocket hits this island.

    **Missile ID = 0**:
      - range: 2
      - damage: 5
      - altitude: 1
    
    **Missile ID = 1**:
      - range: 4
      - damage: 4
      - altitude: 2
   
    **Missile ID = 2**:
      - range: 6
      - damage: 3
      - altitude: 3

    **Missile ID = 3**:
      - range: 8
      - damage: 2
      - altitude: 4

6. **Turn**: In a single turn player can move ship to empty sector on the map, shoot to chosen ship or save file with current game state. At the end of the turn user is asked to confirm his decision or to cancel. If the cancel option is chosen, turn goes back to the beggining.

## 📄 File handling

1. **Saving data to file**: If you want to save current game state file, you have to chose option **Save** during your turn. Then the player will be asked to type the name of the file, in which
game will be saved. If the file does not exist, it will be created. Otherwise the existing file will be overwritten.

2. **Loading data from file**: Loading data from file can be done by choosing option **Load Game** in the menu and then by writting file name. IF the filename is incorect, the error will occur.
The file with game state has strictly defined form. Any deviation from this form is associated with the inability to load the game state correctly.

3. **Correct structure of file**:
Game;<board size>;<index of the player, who is on the move: 0 or 1>;
Islands;<number of islands rows, each row is filles with islands with the same height, for example n = 3 >;
<height of island1>;<number of x, y pairs of coordinates, for example n=2>;<x1>;<y1>;<x2>;<y2>;
<height of island2>;<number of x, y pairs of coordinates, for example n=3>;<x1>;<y1>;<x2>;<y2>;<x3>;<y3>;
<height of island3>;<number of x, y pairs of coordinates, for example n=1>;<x1>;<y1>;
Ships1;<number of ships, for example n = 2>;
<Ship class name: Submarine, Destroyer, Cruiser or Batleship>;<ship name(one letter)>;<number of x, y pairs of coordinates, for example n=2>;<x1>;<y1>;<x2>;<y2>;
<Ship class name: Submarine, Destroyer, Cruiser or Batleship>;<ship name(one letter)>;<number of x, y pairs of coordinates, for example n=2>;<x1>;<y1>;<x2>;<y2>;
Player1;<player's 1 name>;
Ships2;<number of ships, for example n = 1>;
<Ship class name: Submarine, Destroyer, Cruiser or Batleship>;<ship name(one letter)>;<number of x, y pairs of coordinates, for example n=2>;<x1>;<y1>;<x2>;<y2>;
Player2;<player's 2 name>;














