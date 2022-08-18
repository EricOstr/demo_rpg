# C++ Demo Role Player Game

This is a personal project where I extend a terminal based role player game built from scratch ([link for original game](https://github.com/codetechandtutorials/demo_rpg/releases/tag/ep20)). 

The goal of the game is to slay as many monsters as possible. On startup, the player may choose to play as a Cleric, Warrior, Rogue or Wizard - each having their own strengths and weaknesses. Using the keyboard characters a,w,s,d the player moves around the game board chasing monsters, equip items from inventory or examine the players statistics in the character sheet. If the monster and player clash, the control shifts to 'battle mode'. This is a turn based fight sequence where the player may attack, use items or exhaust abilities. Once the player slays a monster, the player receives experience points (XP) and possibly new items. Accumulating XP allows the player to level up, which increases the player's stats (HP, Armor, Resistance, Strength, Agility, Intelligence). The game ends when the player is defeated by a monster and a total score is shown.



#### Major Extension Includes:
* Implementing multithreading
* Adding multiple monsters
* CMake implementation
* Unit Testing static library 'demo_rpg' with GoogleTest


Although the game in its current form is functional, some glitches exist.


### Start Menu
<img width="717" alt="start" src="https://user-images.githubusercontent.com/45294679/185206967-374249fa-d53c-454e-a9b1-94654cb9dcbd.png">


### Game Board
<img width="711" alt="game_board" src="https://user-images.githubusercontent.com/45294679/185207282-5611c40e-ce33-4391-bba2-9a8c331df18f.png">


### Inventory Mode
<img width="709" alt="inventory_view" src="https://user-images.githubusercontent.com/45294679/185207606-1816b7a4-28a8-463f-8338-0cf05ff70412.png">


### Battle Mode
<img width="707" alt="fight_sequence" src="https://user-images.githubusercontent.com/45294679/185207478-a47fbb56-c206-4ffd-b482-3ca86aba52bb.png">


### Battle Victory
<img width="754" alt="victory" src="https://user-images.githubusercontent.com/45294679/185211525-fe6a6fa4-3b11-4635-9f48-ef2727debb41.png">


### Character Sheet
<img width="709" alt="character_sheet" src="https://user-images.githubusercontent.com/45294679/185207699-84391277-9249-40a1-b5f0-884d721224cb.png">


### Game End
<img width="714" alt="end" src="https://user-images.githubusercontent.com/45294679/185210277-094a5a8d-fa02-45b7-a5e1-d34eddf57621.png">
