// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver == true) 
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Setup game variables
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Welcome the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("You must enter a %i letter word."), HiddenWord.Len());
        return;
    }

    if (IsIsogram(Guess) == false)
    {
        PrintLine(TEXT("You must enter an isogram"));
        return;
    }

    if (--Lives <= 0) 
    {
        PrintLine(TEXT("You have Lost!"));
        EndGame();
        return;
    }
    PrintLine(TEXT("You have %i lives remaining"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    // Map to keep track of the letters in the word
    TMap<TCHAR, bool> LetterMap;
    for (TCHAR Letter : Word)
    {
        if (LetterMap.Contains(Letter) == true)
        {
            // If the letter has been seen before, it's not an isogram
            return false;
        }
        
        LetterMap.Add(Letter, true);
    }

    // If the loop went through all the letters in the word
    // without returning, it's an isogram
    return true;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Game over! Press enter to continue..."));
}