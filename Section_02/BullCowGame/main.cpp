#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//funkcje
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; 

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		} 
	while (bPlayAgain);

	return 0;
}

//to jest takie intro
void PrintIntro()
{
	std::cout << "Witaj na moim ranczo smiertelniku, czy dasz rade odgadnac tajemne haslo farmera?.\n";
	std::cout << std::endl;
	std::cout << "          (   )        ___ " << std::endl;
	std::cout << "    ______(0 0)       (o o)______ " << std::endl;
	std::cout << "   /      \\ /         |O|       |) " << std::endl;
	std::cout << "  / | BYK  |              |KROWA |( " << std::endl;
	std::cout << " *  |----- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Odgadnij " << BCGame.GetHiddenWordLength();
	std::cout << " literowe haslo lub zgin\n";
	std::cout << std::endl;
	return;
}

//gransko
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Byki = " << BullCowCount.Bulls;
		std::cout << ". Krowy = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

	//wez guessa
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// wez guess od gracza
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Proba " << CurrentTry << " z " << BCGame.GetMaxTries();
		std::cout << ". Zgaduj: ";
		std::getline(std::cin, Guess);

		// status
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) 
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Twoje slowo nie jest " << BCGame.GetHiddenWordLength() << " literowe!\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Slowo nie moze miec powtarzajacych sie liter!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "NIE UZYWAJ DUZYCH LITER!\n\n";
			break;
		default:
			// guess jest git
			break;
		}
	} 
	while (Status != EGuessStatus::OK);
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Jeszcze raz smiertelniku (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "KONGRATULACJE, ZROBILES TO ZUCHU\n";
	}
	else
	{
		std::cout << "PREZGRALES, ZAPRASZAM DO PIEKLA\n";
	}
}