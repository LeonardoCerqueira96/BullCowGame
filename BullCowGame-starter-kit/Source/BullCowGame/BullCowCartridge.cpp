// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Magic Number Remove!
    PrintLine(TEXT("Press enter to continue..."));

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
    }
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(FString::Printf(TEXT("You must enter a %d letter word."), HiddenWord.Len()));
        }

        PrintLine(TEXT("You have Lost!"));
    }
    
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = 5;
}