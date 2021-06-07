// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PopulateWordLists();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver) 
    {
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess.ToUpper() == HiddenWord)
    {
        PrintLine(TEXT("Correct! - The word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Please choose a %i letter word!"), HiddenWord.Len());
        return;
    }

    if (!CheckIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters!\nTry Again"));
        return;
    }
    RemoveLife();
    FBullCowCount Score = GetBullCows(Guess.ToUpper());
    PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls, Score.Cows);
}

const bool UBullCowCartridge::CheckIsogram(const FString& Word)
{
    for (int32 index = 0; index < Word.Len(); index++)
    {
        for (int32 comparison = index+1; comparison < Word.Len(); comparison++)
        {
            if (Word[index] == Word[comparison])
            {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::SetupGame()
{
    ClearScreen();
    HiddenWord = "";
    HiddenWord = Words[FMath::RandRange(0,Words.Num()-1)].ToUpper();
    Lives = HiddenWord.Len()*2;
    bGameOver = false;
    DisplayWelcomeMessage();
    DebugPrintouts();
}

const void UBullCowCartridge::DisplayWelcomeMessage()
{
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type your guess.\nPress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::RemoveLife()
{
    --Lives;
    if (Lives <= 0)
    {
        GameOver();
    }
    else
    {
        DisplayLives();
    }
}

const void UBullCowCartridge::DisplayLives()
{
    if (Lives == 1)
    {
        PrintLine(TEXT("Incorrect Guess!\nYou have 1 life remaining"));
    }
    else
    {
        PrintLine(TEXT("Incorrect Guess!\nYou have %i lives remaining"), Lives);
    }
}

void UBullCowCartridge::GameOver()
{
    PrintLine(TEXT("Game Over - The correct word was %s"), *HiddenWord);
    EndGame();
}

void UBullCowCartridge::PopulateWordLists()
{
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordsList/ukenglish.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    Words = GetValidWords(Words);
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList)
{
    TArray<FString> ToReturn;
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && CheckIsogram(Word))
        {
            ToReturn.Emplace(Word);
        }
    }
    return ToReturn;
}

const void UBullCowCartridge::DebugPrintouts()
{
    PrintLine(TEXT("****Debug Info****"));
    PrintLine(TEXT("Number of valid words = %i"), Words.Num());
    PrintLine(TEXT("The hidden word is %s"), *HiddenWord);
}

const FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess)
{
    FBullCowCount Count;

    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if (HiddenWord[i] == Guess[i])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 j = 0; j < HiddenWord.Len(); j++)
        {
            if (Guess[i] == HiddenWord[j])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}

