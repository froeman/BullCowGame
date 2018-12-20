/*
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// all values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame {

public:
	FBullCowGame(); // constructor

	FString GetHiddenWord() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString); 

private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyDifficulty;
	FString MyHiddenWord;

	bool bGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};