// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
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
    for (int32 PivotIndex = 0; PivotIndex < Word.Len(); ++PivotIndex)
    {
        for (int32 CompareIndex = PivotIndex + 1; CompareIndex < Word.Len(); ++CompareIndex)
        {
            if (Word[PivotIndex] == Word[CompareIndex])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for (FString Word : WordList)
    {
        if ((Word.Len() >= 3 && Word.Len() <= 9) && IsIsogram(Word) == true)
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Game over! Press enter to continue..."));
}