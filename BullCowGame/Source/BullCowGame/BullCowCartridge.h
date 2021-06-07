// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& PlayerInput) override;
	void ProcessGuess(const FString& Guess);
	const bool CheckIsogram(const FString& Word);
	void SetupGame();
	const void DisplayWelcomeMessage();
	void EndGame();
	void RemoveLife();
	const void DisplayLives();
	void GameOver();
	void PopulateWordLists();
	TArray<FString> GetValidWords(const TArray<FString>& WordList);
	const void DebugPrintouts();
	const FBullCowCount GetBullCows(const FString& Guess);

	// Your declarations go below!
	private:
		TArray<FString> Words;
		FString HiddenWord;
		int32 Lives;
		bool bGameOver;
};
