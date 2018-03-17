/* This is the console executable. Makes use of BullCow class.
   This acts as the view in a MVC pattern, responsible for user
   interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "main.h"
#include "FBullCowGame.h"

// Aliases to normalize to Unreal datatypes
using FText = std::string;
using int32 = int;

// local prototypes - forward declaration
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game - singleton

void PrintIntro() {
	// Introduce the game
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Try to guess the " << BCGame.GetHiddenWordLength() << "-letter isogram am I thinking of!" << std::endl;
	return;
};

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
			std::cout << "Your guess is valid." << std::endl;
		}
	}
	
	return Guess;
}

void PrintGameSummary()
{
	std::string finalMessage;
	if (BCGame.IsGameWon())
	{
		finalMessage = "YOU FOUND THE HIDDEN WORD! YOU WIN!";
	}
	else
	{
		finalMessage = "Sorry, you lose. Better luck next time.";
	}

	std::cout << finalMessage << std::endl;
	std::cout << std::endl;

	return;
}

// Play a signle game to completion: either the player wins or runs out of turns
void PlayGame()
{
	BCGame.Reset();

	// loop for the number of turns and ask for a guess
	while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries() && !BCGame.IsGameWon())
	{
		std::cout << std::endl;
		FText Guess = GetValidGuess();

		// let the game evaluate the guess
		FBullCowCount GuessCounts = BCGame.EvaluateGuess(Guess);
		// print number of bulls and cows
		std::cout << "Your guess was: \"" << Guess << "\"" << std::endl;
		std::cout << "Bulls = " << GuessCounts.Bulls << std::endl;
		std::cout << "Cows = " << GuessCounts.Cows << std::endl;
	}

	PrintGameSummary();

	return;
}

bool AskToPlayAgain()
{
    // Since the word is not changed across "tries", I think it's better to frame
    // this as more tries than playing again.
    // TODO: give the option for a new isogram or to keep trying
	std::cout << "Do you want to keep trying? (y/n)";
	FText Response = "";
	getline(std::cin, Response);

	bool is_affirmative = (Response[0] == 'y' || Response[1] == 'Y');

	return is_affirmative;
}


// APPLICATION ENTRY POINT
int main()
{

	bool bPlayAgain = false;
	do {
		PrintIntro();

		PlayGame();

		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);

	return 0;
}
