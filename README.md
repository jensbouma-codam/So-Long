# Codam-so_long

[![C/C++ CI](https://github.com/jensbouma/Codam-so_long/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/jensbouma/Codam-so_long/actions/workflows/c-cpp.yml)

## Description
This project is a very small 2D game. The goal is to work with textures. And to interact with some very basic gameplay elements.

## Usage
```
make
./so_long maps/map.ber
```

## Maps

## Mandatory Features
- [x] The use of images of 64x64 pixels
- [ ] The game must be able to be closed manually
- [ ] The game window must fit its content size
- [ ] The game must take as a first argument a map description file with the .ber extension
- [ ] The map must be composed of only 5 possible characters: 0 for an empty space, 1 for a wall, C for a collectible, E for the exit and P for the player’s starting position
- [ ] The map must be closed/surrounded by walls, if not the program must return an error
- [ ] Except for the map content, each type of element can be separated by one and only one space

## Bonus Features
- [x] The use of images of 64x64 pixels
- [ ] The game must be able to be closed manually
- [ ] The game window must fit its content size
- [ ] The game must take as a first argument a map description file with the .ber extension
- [ ] The map must be composed of only 5 possible characters: 0 for an empty space, 1 for a wall, C for a collectible, E for the exit and P for the player’s starting position
- [ ] The map must be closed/surrounded by walls, if not the program must return an error
- [ ] Except for the map content, each type of element can be separated by one and only one space
- [ ] The map must be rectangular
- [ ] The map must be parsed as it looks like in the example
- [ ] In case of any error in the map, the program must return “Error\n” followed by an explicit error message of your choice
- [ ] The minimum size of the map must be 3x3
- [ ] The map must be a valid map, meaning that:
- [ ] All the elements of the map must be reachable, if not the program must return an error
- [ ] There must be at least one exit, one collectible and one player position, if not the program must return an error
- [ ] The map must be closed/surrounded by walls, if not the program must return an error
- [ ] The map must not have any floating walls, if not the program must return an error
- [ ] The map must not have any character after the map content, if not the program must return an error
- [ ] The map must have at least one collectible, if not the program must return an error
- [ ] When the player collects all the collectibles, the program must return 0
- [ ] The player position can’t be a collectible, an exit or a wall, if not the program must return an error
- [ ] When the player walks into a wall, nothing happens
- [ ] When the player walks into an empty space, he must displace
- [ ] When the player collects a collectible, it disappears from the map
- [ ] When the player arrives on the exit, if all collectibles have been collected the program must return 0, otherwise it must return 1
- [ ] The player must be able to move up, down, left and right
- [ ] The player must be able to close the window with the red cross
- [ ] The program must take screenshots with the --save flag, first frame, last frame, and every frame separated by a minimum of 10 frames
- [ ] The program must display an animated sprite of a walking character, the sprite must be a black square (no need to create a real sprite file)
- [ ] The player’s character must turn to the direction it moves

## Controls
- W A S D to move
- ESC to exit
- Collect all collectibles to win
- You can't walk through walls
- You can't walk through the exit before collecting all collectibles
  
## Screenshots
None

## Bonus
- [ ] Animations
- [ ] Sounds
- [ ] Enemies
- [ ] Levels
- [ ] Score
- [ ] Menu
- [ ] Save/Load
- [ ] Map editor
- [ ] Multiplayer
- [ ] Online multiplayer
- [ ] Online highscores
- [ ] Online map editor
- [ ] Online map sharing
- [ ] Online map voting
- [ ] Online map rating
- [ ] Online map highscores

## Dependencies
- [libft]
- [libmlx42]
- [libglfw3]

## Norm
- Functions must not exceed 25 lines
- No more than 5 function-definitions in a .c file
- One instruction per line
- One single variable declaration per line; cannot stick declaration and initialisation on the same line
- No more than 5 variables per bloc
- No more than 4 parameters per function
- Forbidden keywords are: [for] [do ... while] [switch] [case] [goto]
