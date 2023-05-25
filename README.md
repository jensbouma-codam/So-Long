# Codam-so_long

[![C/C++ CI](https://github.com/jensbouma/Codam-so_long/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/jensbouma/Codam-so_long/actions/workflows/c-cpp.yml)

## Description
Create a basic 2D game in which a dolphin
escapes Earth after eating some fish. Instead of
a dolphin, fish, and the Earth, you can use any
character, any collectible and any place you want.

## Mandatory part
- [x] Program name must be so_long
- [ ] Turn in files: *.c, *.h, Makefile, maps, textures
- [x] Makefile must compile the project and must contain the usual rules (all, clean, fclean, re)
- [x] Makefile doesn't relink
- [ ] The following libc functions are allowed: malloc, free, write, open, read, close, perror, strerror, exit
- [ ] All functions of the math libary are allowed
- [ ] All the functions from the MinilibX and MLX42 libraries are allowed
- [x] LibFT and ft_printf are allowed
- [x] Program take a map as first argument.

## Game
- [ ] The player's goal is to collect every collectible and then exit the map chosing the shortest possible route.
- [x] The player can move using the W, A, S, D keys.
- [x] The player should be able to move in 4 directions (left, right, up, down).
- [ ] The player can't move through walls.
- [ ] At every move the program must display the number of movements.
- [x] Use a 2D view.
- [x] The program has to display the image in a window.
- [x] The management of your window must remain smooth: changing to another window, minimizing, etc.
- [x] Pressing ESC must close the window and quit the program cleanly.

## Map
- [x] The program has to take a map with the .ber extension as a first argument.
- [ ] The map has to be constructed with 3 components: empty space, walls, collectibles.
- [x] The map can be composed of only these 5 characters: 0 for an empty space, 1 for a wall, C for a collectible, E for the exit and P for the player’s starting position.
- [x] The map must contain one exit, one starting position and at least one collectible.
- [x] If the map contains a duplicate start and or exit the program must return an error.
- [ ] The map must be rectangular.
- [ ] The map must be closed/surrounded by walls, if not the program must return an error.
- [ ] The map should have a valid path.
- [ ] The program should be able to parse any kind of map, as long as it respects the maps rules.
- [ ] If any misconfiguration of any kind is encountered in the file, the program must return return "Error\n" followed by an explicit error message of your choice.


## Usage
```
make
./bin/so_long maps/map.ber
```

## Maps
```
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
```

## Common Instructions
- Project is written in C
- Project is in accordance with the Norm (see below)
- Functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors. If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- All heap allocated memory space must be properly freed when necessary. No leaks can be tolerated.
- If the subject requires it, you must submit a Makefile which will compile your source files to the required output with the flags -Wall, -Wextra and -Werror, and your Makefile must not relink.
- Your Makefile must at least contain the rules $(NAME), all, clean, fclean and re.
- To turn in bonuses to your project, you must include a rule bonus to your Makefile, which will add all the various headers, librairies or functions that are forbidden on the main part of the project. Bonuses must be in a different file _bonus.{c/h}.
- If your project allows you to use your libft, you must copy its sources and its associated Makefile in a libft folder with its associated Makefile. Your project’s Makefile must compile the library by using its Makefile, then compile the project.
- We encourage you to create test programs for your project even though this work won’t have to be submitted and won’t be graded. It will give you a chance to easily test your work and your peers’ work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded. If Deepthought is assigned to grade your work, it will be done after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.

## Bonus
- [ ] Animations
- [ ] Make the player lose when he touches an enemy
- [ ] Display the movements count directly on the screen instead of in the shell

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
