/* Game Logic class - Implements game rules
 * No view code or user interaction handling
 */

#pragma once

#include <string>

// Aliases to normalize to Unreal datatypes
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	OK,
	NotIsogram,
	NotLowercase,
	Invalid
};

class FBullCowGame {
public:

	FBullCowGame(); // Constructor

	void Reset();
	void StartGame();
	
	// Getters - const means they can't change member variables' values
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	
	EGuessStatus CheckGuessValidity(FString Guess) const;

	FBullCowCount EvaluateGuess(FString Guess);

	
private:
	// See constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString Word) const;
    bool IsLowerCase(FString Word) const;
};
