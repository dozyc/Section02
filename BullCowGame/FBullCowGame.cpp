#include "FBullCowGame.h"

using int32 = int;

// Getters
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const {return bGameWon; }

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

// receives a VALID guess, increments turn number, returns counts
FBullCowCount FBullCowGame::EvaluateGuess(FString Guess)
{
	// setup return variable
	FBullCowCount GuessCounts;
	
	// loop thru all letters in the guess
	for (int32 guessIdx = 0; guessIdx < Guess.length(); guessIdx++)
	{
		// compare to all letters in the hidden word
		for (int32 hiddenIdx = 0; hiddenIdx < MyHiddenWord.length(); hiddenIdx++)
		{
			if (Guess[guessIdx] == MyHiddenWord[hiddenIdx])
			{
				if (guessIdx == hiddenIdx)
				{
					// Same letter, same place: BULL
					GuessCounts.Bulls++;
				}
				else
				{
					// Same letter, wrong place: COW
					GuessCounts.Cows++;
				}
			}
		}

	}
	// increment turn number
	MyCurrentTry++;
	bGameWon = (GuessCounts.Bulls == MyHiddenWord.length());
	return GuessCounts;
}


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	bGameWon = false;

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;

	return;
}

// Do I even need this function?
void FBullCowGame::StartGame()
{
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// error if the guess isn't an isogram
	if (false)
	{
		return EGuessStatus::NotIsogram;
	}
	// error if the guess isn't all lowercase
	else if (false)
	{
		return EGuessStatus::NotLowercase;
	}
	// otherwise return ok
	else
	{
		return EGuessStatus::OK;
	}
}
