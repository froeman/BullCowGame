#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

void FBullCowGame::Reset()
{
	constexpr int32 CURRENT_TRY = 1;
	MyHiddenWord = GetHiddenWord();
	MyCurrentTry = 1;
	bGameWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 5 },{ 4, 8 },{ 5, 9 },{ 6, 15 } };
	int32 DIFFICULTY = WordLengthToMaxTries[3];
	return DIFFICULTY;
}

FString FBullCowGame::GetHiddenWord() const // TODO create a list of words in each difficulty that can be chosen randomly based on difficulty
{
	TMap<int32, FString> DifficultyToHiddenWord{ { 3, "and" }, { 4, "back" }, { 5, "plane" }, { 6, "planet" } };
	const FString HIDDEN_WORD = DifficultyToHiddenWord[3];
	return HIDDEN_WORD;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if ( !IsIsogram(Guess) ) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if ( !IsLowercase(Guess) )
	{
		return EGuessStatus::Not_Lowercase;
	}	
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) // if they're in the same place
				{ 
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{ 
			return false; // we do not have an isogram
		} 
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}	
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	// handle 0 and 1 letter words
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word) // for all letters of the word
	{
		if (!islower(Letter))
		{
			return false; // we do not have lowercase letters
		}
	}
	return true;
}
