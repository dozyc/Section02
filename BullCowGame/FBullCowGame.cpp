#include "FBullCowGame.h"

using int32 = int;

// Getters
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

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
	return GuessCounts;
}

bool FBullCowGame::IsGameWon() const
{
	// TODO: implement this
	return false;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;

	return;
}

// Do I even need this function?
void FBullCowGame::StartGame()
{
}

EWordStatus FBullCowGame::CheckGuessValidity(FString guessString) const
{
	// TODO: implement this
	return EWordStatus::OK;
}
