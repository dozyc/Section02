/* This is the console executable. Makes use of BullCow class.
   This acts as the view in a MVC pattern, responsible for user
   interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "main.h"
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame; // instantiate a new game

void PrintIntro() {
	// Introduce the game
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Try to guess the " << BCGame.GetHiddenWordLength() << "-letter isogram am I thinking of!" << std::endl;
	return;
};

// TODO: ensure that the guess is valid, don't return until it is
FText GetValidGuess() {
	std::cout << "Guess #" << BCGame.GetCurrentTry() << std::endl;

	EGuessStatus GuessStatus = EGuessStatus::Invalid;
	FText Guess = "";

	while (GuessStatus != EGuessStatus::OK)
	{
		// Prompt the player
		std::cout << "Enter your guess: ";
		// Get a guess from the player
		getline(std::cin, Guess);

		GuessStatus = BCGame.CheckGuessValidity(Guess);

		switch (GuessStatus)
		{
		case EGuessStatus::NotIsogram:
			std::cout << "Please enter an isogram (no repeated characters)." << std::endl;
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "Please enter all lowercase characters." << std::endl;
			break;
		case EGuessStatus::Invalid:
			std::cout << "Your guess is invalid for an unknown reason! Try again." << std::endl;
			break;
		default:
			std::cout << "You entered a valid guess!" << std::endl;
		}
	}
	
	return Guess;
}

void PlayGame()
{
	BCGame.Reset();

	std::cout << BCGame.GetCurrentTry();

	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns and ask for a guess
	// TODO: use the game state to count tries, not this loop
	for (int32 count = 1; count <= MaxTries; count++)
	{
		std::cout << std::endl;
		FText Guess = GetValidGuess();

		// let the game evaluate the guess
		FBullCowCount GuessCounts = BCGame.EvaluateGuess(Guess);
		// print number of bulls and cows
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << "Bulls = " << GuessCounts.Bulls << std::endl;
		std::cout << "Cows = " << GuessCounts.Cows << std::endl;

	}

	// TODO: summarise game
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	getline(std::cin, Response);

	bool is_affirmative = (Response[0] == 'y' || Response[1] == 'Y');

	return is_affirmative;
}


// APPLICATION ENTRY POINT
int main()
{
	PrintIntro();

	bool bPlayAgain = false;
	do {

		PlayGame();

		 bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);

	return 0;
}