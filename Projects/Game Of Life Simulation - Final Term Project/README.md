# Game Of Life Simulation
The **Game of Life**, also known simply as ***Life***, is a cellular automaton devised by the British mathematician **John Horton Conway** in 1970. The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. However, I have implemented the project as a single player/multi player game.<br />
Read more about the rules and the environment from [wikipedia](https://en.wikipedia.org/wiki/Conway's_Game_of_Life)
<br /><br />
My projects consists of two parts:<br />
1. Map Editor
2. Game Of Life
<br />

### Map Editor
  You can make an emty map and customize it as you like, Generate a random map (10%: Energy Blocks, 10%: Mitosis Blocks, 20%: Forbidden Blocks, 60%: Normal Blocks) or edit an existing map! I strongly recommand you write this application before starting the main project; It will come in handy if you run into bugs!<br />
  
### Game Of Life
player has a number of cells in command (More players can participate as well). Each player take some actions on their turns:
#### Move
There are six direction a cell can move to:
- North
- South
- North-East
- North-West
- South-East
- South-West

***Cells cannot move to a FORBIDDEN block and they cannot be in the same block at the same time!***
#### Split
Each cell can split into two, only if these two conditions are met:
 1. Cell must be on a MITOSIS block
 2. Cell must have more than 80% energy level
 In case of an split, the two newly made cells will have 40% evergy
#### Boost
Each cell can boost energy from the block it is on, only if the block is an ENERGY block! In that case, the cell can take upto 15 energy points if the block contains more than 15 energy points, and take whatever energy left if the block contains less than 15 energy points.

<br /><br />
### Notes
- Map, Cell properties, Block types and values must be saved into a binary file after each move (Autosave) so that player can reload the previous game anytime after.
- The visual map cannot be a squeare map. It must look like a Hexagons.
- Each cell has the following properties:
  - X coordinate
  - Y coordinate
  - Energy level
  - Symbol (Indicates which cell belongs to which player)
  - Name (Can be random)
- Each cell can have upto 100 Energy points and cannot absorb any more points.
- Game ends when all ENERGY blocks run out of energy
- Winner is the player who absorbs the most energy from the blocks
<br /><br />
> Best Of Regards - Keivan Ipchi Hagh
