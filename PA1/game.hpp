#ifndef GAME_HPP
#define GAME_HPP

#include "list.hpp"
#include "data.hpp"
#include <string>
#include <vector>
#include <fstream>

struct Player
{
	std::string name;
	int totalPoints;

	Player() : name(""), totalPoints(0) {}
	Player(const std::string& n, int pts) : name(n), totalPoints(pts) {}
};

class Game
{
private:
	List<Data> commands;
	Player players[100];
	int numPlayers;

	void loadCommandsFromCSV();
	void saveCommandsToCSV();
	void loadPlayersFromCSV();
	void savePlayersToCSV();
	std::string trim(const std::string& str);
	std::vector<std::string> parseCSVLine(const std::string& line);
	int findPlayerIndex(const std::string& playerName);
	void generateRandomOptions(const Data& correctCommand, std::vector<std::string>& options);

public:
	Game();
	~Game();

	void displayMenu();
	void showGameRules();
	void playNewGame();
	void loadPreviousGame();
	void addCommand();
	void removeCommand();
	void displayAllCommands();
	void saveAndExit();

	void runGame();
	void playQuestionRound(Player& player, int numQuestions);

	void clearScreen();
	void pauseScreen();
};

#endif
