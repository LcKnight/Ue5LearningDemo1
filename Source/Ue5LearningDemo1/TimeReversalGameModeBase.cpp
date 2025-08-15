// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeReversalGameModeBase.h"

void ATimeReversalGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);


	//Init the time manager
	TimeManager = Cast<ATimeManager>(GetWorld()->SpawnActor(ATimeManager::StaticClass()));
	if (!TimeManager) {
		UE_LOG(LogTemp, Display, TEXT("Failed to create a TimeManager"));
	}
}

ATimeManager* ATimeReversalGameMode::GetTimeManager()
{
	if (!TimeManager) {
		UE_LOG(LogTemp, Display, TEXT("No TIme Manager"));
	}return TimeManager;
}
