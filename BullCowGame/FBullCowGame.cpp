#include "FBullCowGame.h"
#include <map>
#define TMap std::map // Use Unreal type for practice

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

/* IsIsogram runs in O(n) time. Worst case: all letters are touched once.
 * Use LetterSeen hash to keep track of letters that have been seen.
 * LetterSeen is intially empty, accessing LetterSeen[Letter] for the
 * first time returns false.
 * For each letter in the word, check LetterSeen[Letter]. It will be 
 * false only the first time the letter is seen, then immediately set to true.
 * From then on, if LetterSeen[Letter] is accessed
 * again, it will return true, indicating that the letter has already
 * appeared in the word before, so the word is not an isogram.
 *
 */
bool FBullCowGame::IsIsogram(FString Word) const
{
	bool isIsogram = true;
	TMap<char, bool> LetterSeen;

	for (char Letter : Word) // range-based for loop example
	{
		Letter = tolower(Letter); // normalize to lowercase for comparisons

		if (LetterSeen[Letter])
		{
			isIsogram = false;
			break;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return isIsogram;
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
	if (!IsIsogram(Guess))
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
