/* This is the console executable that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class. */
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
int32 ChooseDifficulty();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game which we re-use across plays

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		ChooseDifficulty();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	std::cout << std::endl;

	return 0; // exit the application
}

void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "----------------------------------------- " << std::endl;
	std::cout << "               WELCOME TO                 " << std::endl;
	std::cout << "----------------------------------------- " << std::endl;
	std::cout << "      BULLS        AND        COWS        " << std::endl;
	std::cout << "----------------------------------------- " << std::endl;
	std::cout << "  ,           ,                           " << std::endl;
	std::cout << " /             \\                         " << std::endl;
	std::cout << "((__-^^-,-^^-__))          _-^^-,-^^-_    " << std::endl;
	std::cout << " `-_---' `---_-'         `-_---' `---_-'  " << std::endl;
	std::cout << "  <__|o` 'o|__>           <__|o` 'o|__>   " << std::endl;
	std::cout << "    \\  `  /                \\  `  /      " << std::endl;
	std::cout << "      ): :(                   ): :(       " << std::endl;
	std::cout << "      :o_o:                   :o_o:       " << std::endl;
	std::cout << "        -                       -         " << std::endl;
	std::cout << "            A FUN WORD GAME!              " << std::endl;
	std::cout << std::endl;
	// TODO ask the user if they'd like to start the game or review the rules 1. Start Game | 2. Review Rules
	// TODO move this section to a new game intro function
	/* std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	std::cout << "Rules:\n" << "1. Lowercase only\n" << "2. Isograms only (words with no repeating letters)\n" << "3. Lowercase letters only\n\n"; // TODO move this to the new "rules" function
	std::cout << "You have " << BCGame.GetMaxTries() << " tries. Good Luck!\n\n"; */
	ChooseDifficulty();
	return;
}

int32 ChooseDifficulty()
{ 
	std::cout << "Difficulty is determined by choosing the word length you'd like to try.\n";
	std::cout << "Please choose between 3 and 6 letter words: "; // TODO ask user desired difficulty using 3 to 6 letter words
	return 3;
}

// TODO create new function to print rules of the game

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses
	// while game is NOT won and there are still tries remaining
	while ( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries )
	{
		FText Guess = GetValidGuess();
		
		// submit Valid guess to game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << " | Cows= " << BullCowCount.Cows << "\n\n";
	}
	
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTries = BCGame.GetMaxTries();
		std::cout << "Try " << CurrentTry << " of " << MaxTries << "\nEnter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter lowercase letters only.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (Y/N): ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done! You Win!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
