/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is reponsible for all
user interaction. For game logic see hte FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintInfo();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// entry point for the game
int main()
{
	bool PlayAgain = false;
	do
	{
		PrintInfo();
		PlayGame();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);

	return 0; // exit the application
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	// loop for a number of turns asking for guess
	for (int32 i = 0; i < MaxTries; ++i)
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		// print number of Bulls & Cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}

	// TODO add a game summary
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?" << std::endl;
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// introduce the game
void PrintInfo()
{
	std::cout << "Welcome to Bulls & Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		FText Guess = "";
		getline(std::cin, Guess);
		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please all lowercase letters.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram.\n";
			break;
		default:
			return Guess;
		}
	}
	while (Status == EGuessStatus::OK);
}