# Sokoban
Sokoban SDL2 implementation

Written using C++

![](https://raw.githubusercontent.com/Blackweather/Sokoban/master/screenshots/screenshot.png)

# Goal of the game
Move the boxes to their positions.
You cannot push more than one box at a time.

# Controls
> arrow keys - movement
> ESC - exit game
> N - start new game on current level (moves player and boxes to starting positions)
> P - next level

# How to make maps
It's really to make your own maps in this implementation.
It's done using .txt files.
There are already 14 maps in the map folder.

**To make a map**
> create a new mapXX.txt file in maps folder
>> XX should be replaced with next map number
> change the constant MAP_COUNT in Game.h file to match new number of maps

**How to fill the map text file?**

First line is a single number corresponding to **height** of map (max 14, because of window size)
Second line is a single number corresponding to **width** of map

Next we have lines filled with characters corresponding to specific pieces of map
The number of lines should be equal to the height of map.
Number of characters in a line should be equal to the width of map.

**Available characters:**

**G** - grass (empty tile outside of walls)

![](https://raw.githubusercontent.com/Blackweather/Sokoban/master/img/Grass.bmp)

**E** - empty (empty tile inside walls)

![](https://raw.githubusercontent.com/Blackweather/Sokoban/master/img/Ground.bmp)

**W** - wall (tile you can't walk through)

![](https://raw.githubusercontent.com/Blackweather/Sokoban/master/img/Wall.bmp)

**F** - finish (final place for box)

![](https://raw.githubusercontent.com/Blackweather/Sokoban/master/img/EndPoint.bmp)

**B** - box (starting place for box)

![](https://raw.githubusercontent.com/Blackweather/Sokoban/master/img/Crate.bmp)

**P** - player (starting place for player character)
