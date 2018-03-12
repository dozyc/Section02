#pragma once

#include <string>

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

enum class EResetStatus
{
	OK,
	NoHiddenWord
};

class FBullCowGame {
public:

	FBullCowGame(); // constructor

	void Reset(); // TODO - maybe do a non void return, maybe add an arg?;
	void StartGame();
	
	// Getters - const means they can't change member variables values
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	
	EGuessStatus CheckGuessValidity(FString Guess) const;

	FBullCowCount EvaluateGuess(FString Guess);

	
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString Word) const;
};