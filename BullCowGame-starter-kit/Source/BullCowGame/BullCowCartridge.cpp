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
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You have Won!"));
            EndGame();
        }
        else
        {
            if (--Lives <= 0) 
            {
                PrintLine(TEXT("You have Lost!"));
                EndGame();
            }
            else
            {
                if (Input.Len() != HiddenWord.Len())
                {
                    PrintLine(TEXT("You must enter a %i letter word."), HiddenWord.Len());
                }
                PrintLine(TEXT("You have %i lives remaining"), Lives);
            }
        }       
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

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Game over! Press enter to continue..."));
}