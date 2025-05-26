README - Linux Commands Matching Game (PA1)
===========================================

Overview:
This is a terminal game where the player reads a Linux command and matches it with the correct description.

Build Instructions:
Compile and run the project using the following:

	g++ -std=c++11 *.cpp -o PA1
	./PA1

Advantages & Disadvantages:

Linked list for Commands:
-Advantage: Fast insert and deletion when loading or modifying commands (O(1))
-Disadvantage: Random access is inefficient, this makes the indexing slower when picking questions

Array for Player Profiles:
-Advantage: Makes indexing/searching by player names faster
-Disadvantage: Fixed Size; There is no dynamic growth so fixed amount of total players
