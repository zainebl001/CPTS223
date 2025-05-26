#include "game.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

Game::Game()
{
	numPlayers = 0;
	srand(time(nullptr));
	loadCommandsFromCSV();
	loadPlayersFromCSV();
}

Game::~Game() {}

void Game::runGame()
{
	int choice;
	bool running = true;

	std::cout << "Welcome to the Linux Commands Matching Game!" << std::endl;
	std::cout << "============================================" << std::endl;

	while (running)
	{
		displayMenu();
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cin.ignore();

		switch (choice)
		{
			case 1:
				showGameRules();
				break;
			case 2:
				playNewGame();
				break;
			case 3:
				loadPreviousGame();
				break;
			case 4:
				addCommand();
				break;
			case 5:
				removeCommand();
				break;
			case 6:
				displayAllCommands();
				break;
			case 7:
				saveAndExit();
				running = false;
				break;
			default:
				std::cout << "Invalid choice. Please try again." << std::endl;
				pauseScreen();
		}
	}
}

void Game::displayMenu()
{
	clearScreen();
	std::cout << "\n=== MAIN MENU ===" << std::endl;
	std::cout << "1. Game Rules" << std::endl;
	std::cout << "2. Play New Game" << std::endl;
	std::cout << "3. Load Previous Game" << std::endl;
	std::cout << "4. Add Command" << std::endl;
	std::cout << "5. Remove Command" << std::endl;
	std::cout << "6. Display All Commands" << std::endl;
	std::cout << "7. Save and Exit" << std::endl;
	std::cout << "=================" << std::endl;
}

void Game::showGameRules()
{
	clearScreen();
	std::cout << "\n=== GAME RULES ===" << std::endl;
	std::cout << "1. You will be presented with Linux commands and multiple choice descriptions." << std::endl;
	std::cout << "2. Choose the correct description for each command." << std::endl;
	std::cout << "3. Correct answers award points based on command difficulty." << std::endl;
	std::cout << "4. Wrong answers deduct 1 point from your total." << std::endl;
	std::cout << "5. Your progress is saved and can be resumed later." << std::endl;
	std::cout << "6. Try to achieve the highest score possible!" << std::endl;
	std::cout << "==================" << std::endl;
 	pauseScreen();
}

void Game::playNewGame()
{
	clearScreen();
	std::string playerName;
	int numQuestions;

	std::cout << "\n=== NEW GAME ===" << std::endl;
	std::cout << "Enter your name: ";
	std::getline(std::cin, playerName);

	if (playerName.empty())
	{
		std::cout << "Invalid name. Returning to main menu." << std::endl;
		pauseScreen();
		return;
	}

	std::cout << "How many questions would you like to answer? ";
	std::cin >> numQuestions;
	std::cin.ignore();
	
	if (numQuestions <= 0 || numQuestions > commands.getSize()) 
	{
		std::cout << "Invalid number of questions. Maximum available: "
			<< commands.getSize() << std::endl;
		pauseScreen();
		return;
	}

	int playerIndex = findPlayerIndex(playerName);
	if (playerIndex == -1)
	{
		players[numPlayers] = Player(playerName, 0);
		playerIndex = numPlayers;
		numPlayers++;
	}

	playQuestionRound (players[playerIndex], numQuestions);
}

void Game::loadPreviousGame()
{
	clearScreen();
	std::string playerName;

	std::cout << "\n=== LOAD PREVIOUS GAME ===" << std::endl;
	std::cout << "Enter your name: ";
	std::getline(std::cin, playerName);

	int playerIndex = findPlayerIndex(playerName);
	if (playerIndex == -1)
	{
		std::cout << "Player not found. Starting with 0 points." << std::endl;
		players[numPlayers] = Player(playerName, 0);
		playerIndex = numPlayers;
		numPlayers++;
	}
	else
	{
		std::cout << "Welcome back, " << playerName << "!" << std::endl;
		std::cout << "Your current score: " << players[playerIndex].totalPoints << " points" << std::endl;
	}

	int numQuestions;
	std::cout << "How many questions would you like to answer? ";
	std::cin >> numQuestions;
	std::cin.ignore();

	if (numQuestions <=0 || numQuestions > commands.getSize()) 
	{
		std::cout << "Invalid number of questions. Maximum available: "
			<< commands.getSize() << std::endl;
		pauseScreen();
		return;
	}

	playQuestionRound(players[playerIndex], numQuestions);
}

void Game::playQuestionRound(Player& player, int numQuestions)
{
	if (commands.isEmpty())
	{
		std::cout << "No commands available to play!" << std::endl;
		pauseScreen();
		return;
	}
	
	int correctAnswers = 0;
	int pointsEarned = 0;

	for (int i = 0; i < numQuestions; i++)
	{
		clearScreen();
		std::cout << "\n=== QUESTION " << (i + 1) << " of " << numQuestions << " ===" << std::endl;
		std::cout << "Player: " << player.name << " | Current Points: " << player.totalPoints << std::endl;
		std::cout << "========================================" << std::endl;
		
		int randomIndex = rand() % commands.getSize();
		Data currentCommand = commands.getDataAtIndex(randomIndex);

		std::vector<std::string> options;
		generateRandomOptions(currentCommand, options);

		std::cout << "\nWhat does the command '" << currentCommand.getCommand() << "' do?" << std::endl;
		for (int j = 0; j < options.size(); j++)
		{
			std::cout << (j + 1) << ". " << options[j] << std::endl;
		}

		int userChoice;
		std::cout << "\nEnter your choice (1-" << options.size() << "): ";
		std::cin >> userChoice;
		std::cin.ignore();

		if (userChoice >= 1 && userChoice <= options.size())
		{
			if (options[userChoice - 1] == currentCommand.getDescription())
			{
				std::cout << "\nCorrect! +" << currentCommand.getPoints() << " points" << std::endl;
				player.totalPoints += currentCommand.getPoints();
				pointsEarned += currentCommand.getPoints();
				correctAnswers++;
			}
			else
			{
				std::cout << "\nIncorrect! -1 point" << std::endl;
				std::cout << "Correct answer: " << currentCommand.getDescription() << std::endl;
				player.totalPoints -= 1;
				pointsEarned -= 1;
			}
		}
		else
		{
			std::cout << "\nInvalid choice! -1 point" << std::endl;
			player.totalPoints -= 1;
			pointsEarned -= 1;
		}

		pauseScreen();
	}

	clearScreen();
	std::cout << "\n=== GAME SUMMARY ===" << std::endl;
	std::cout << "Player: " << player.name << std::endl;
	std::cout << "Questions answered: " << numQuestions << std::endl;
	std::cout << "Correct answers: " << correctAnswers << std::endl;
	std::cout << "Points earned this round: " << pointsEarned << std::endl;
	std::cout << "Total points: " << player.totalPoints << std::endl;
	std::cout << "===================" << std::endl;
	pauseScreen();
}

void Game::generateRandomOptions(const Data& correctCommand, std::vector<std::string>& options)
{
	options.clear();
	options.push_back(correctCommand.getDescription());

	std::vector<std::string> allDescriptions;
	Node<Data>* current = commands.getHead();
	while (current != nullptr)
	{
		if (current->getData().getDescription() != correctCommand.getDescription() &&
		!current->getData().getDescription().empty())
		{
			allDescriptions.push_back(current->getData().getDescription());
		}
		current = current->getNext();
	}

	if (allDescriptions.size() >= 2)
	{
		std::random_shuffle(allDescriptions.begin(), allDescriptions.end());
		options.push_back(allDescriptions[0]);
		options.push_back(allDescriptions[1]);
	}
	else
	{
		options.push_back("Display system information");
		options.push_back("Network configuration tool");
	}

	std::random_shuffle(options.begin(), options.end());
}

void Game::addCommand()
{
	clearScreen();
	std::string command, description;
	int points;

	std::cout << "\n=== ADD COMMAND ===" << std::endl;
	std::cout << "Enter command name: ";
	std::getline(std::cin, command);

	if (command.empty())
	{
		std::cout << "Invalid command name." << std::endl;
		pauseScreen();
		return;
	}

	Node<Data>* current = commands.getHead();
	while (current != nullptr)
	{
		if (current->getData().getCommand() == command)
		{
			std::cout << "Command alread exists!" << std::endl;
			pauseScreen();
			return;
		}
		current = current->getNext();
	}

	std::cout << "Enter points value: ";
	std::cin >> points;
	std::cin.ignore();

	if (points <= 0)
	{
		std::cout << "Points must be positive." << std::endl;
		pauseScreen();
		return;
	}

	Data newCommand(command, description, points);
	commands.insertAtFront(newCommand);

	std::cout << "Command added Successfully!" << std::endl;
	pauseScreen();
}

void Game::removeCommand()
{
	clearScreen();
	std::string command;

	std::cout << "\n=== REMOVE COMMAND ===" << std::endl;
	std::cout << "Enter command name to remove: ";
	std::getline(std::cin, command);

	Data searchData(command, "", 0);
	if (commands.removeNode(searchData))
	{
		std::cout << "Command removed successfully!" << std::endl;
	}
	else
	{
		std::cout << "Command not found!" << std::endl;
	}
	pauseScreen();
}

void Game::displayAllCommands()
{
	clearScreen();
	std::cout << "\n=== ALL COMMANDS ===" << std::endl;

	if (commands.isEmpty())
	{
	std::cout << "No commands available." << std::endl;
	}
	else
	{	
		Node<Data>* current = commands.getHead();
		int count = 1;
		while (current != nullptr)
		{
			std::cout << count << ". " << current->getData() << std::endl;
			current = current->getNext();
			count++;
		}
	}

	std::cout << "\nTotal commands: " << commands.getSize() << std::endl;
	pauseScreen();
}

void Game::saveAndExit()
{
	std::cout << "\nSaving game data..." << std::endl;
	saveCommandsToCSV();
	savePlayersToCSV();
	std::cout << "Game saved successfully. Thank you for playing!" << std::endl;
}

void Game::loadCommandsFromCSV()
{
	std::ifstream file("commands.csv");
	if (!file.is_open())
	{
		std::cout << "Warning: Could not open commands.csv. Starting with empty command list." << std::endl;
		return;
	}
	
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		std::vector<std::string> tokens = parseCSVLine(line);
		if (tokens.size() >= 3)
		{
			std::string command = trim(tokens[0]);
			std::string description = trim(tokens[1]);
			int points = std::stoi(tokens[2]);

			Data newCommand(command, description, points);
			commands.insertAtFront(newCommand);
		}
	}
	file.close();
}

void Game::saveCommandsToCSV()
{
	std::ofstream file("commands.csv");
	if (!file.is_open())
	{
		std::cout << "Error: Could not save commands.csv" << std::endl;
		return;
	}

	Node<Data>* current = commands.getHead();
	while (current != nullptr)
	{
		const Data& cmd = current->getData();
		file << cmd.getCommand() << ",\"" << cmd.getDescription() << "\"," << cmd.getPoints() << std::endl;
		current = current->getNext();
	}
	file.close();
}

void Game::loadPlayersFromCSV()
{
	std::ifstream file("profiles.csv");
	if (!file.is_open())
	{
	return;
	}

	std::string line;
	while (std::getline(file, line) && numPlayers < 100)
	{
		if (line.empty()) continue;

		std::vector<std::string> tokens = parseCSVLine(line);
		if (tokens.size() >= 2)
		{
			std::string name = trim(tokens[0]);
			int points = std::stoi(tokens[1]);

			players[numPlayers] = Player(name, points);
			numPlayers++;
		}
	}
	file.close();
}

void Game::savePlayersToCSV()
{
	std::ofstream file("profiles.csv");
	if (!file.is_open())
	{
		std::cout << "Error: Could not save profiles.csv" << std::endl;
		return;
	}

	for (int i =0; i < numPlayers; i++)
	{
		file << players[i].name << "," << players[i].totalPoints << std::endl;
	}
	file.close();
}

std::string Game::trim(const std::string& str)
{
	std::string result = str;

	if (result.front() == '"' && result.back() == '"')
	{
		result = result.substr(1, result.length() - 2);
	}

	size_t start = result.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
	{
		return "";
	}
	size_t end = result.find_last_not_of(" \n\r\n");

	return result.substr(start, end - start + 1);
}

std::vector<std::string> Game::parseCSVLine(const std::string& line)
{
	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string token;
	bool inQuotes = false;
	std::string currentToken = "";

	for (char c : line)
	{
		if (c == '"')
		{
			inQuotes = !inQuotes;
			currentToken += c;
		}
		else if (c == ',' && !inQuotes)
		{
			tokens.push_back(currentToken);
			currentToken = "";
		}
		else
		{
			currentToken += c;
		}
	}
	tokens.push_back(currentToken);

	return tokens;
}

int Game::findPlayerIndex(const std::string& playerName)
{
	for (int i = 0; i < numPlayers; i++)
	{
		if (players[i].name == playerName)
		{
			return i;
		}
	}
	return -1;
}

void Game::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void Game::pauseScreen()
{
	std::cout << "\nPress Enter to Continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
