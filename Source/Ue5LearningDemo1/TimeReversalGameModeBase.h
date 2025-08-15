// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameMode.h"


#include "TimeManager.h"

#include "TimeReversalGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class UE5LEARNINGDEMO1_API ATimeReversalGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

public:
	UFUNCTION(BlueprintCallable)
	ATimeManager* GetTimeManager();
protected:
	UPROPERTY(BlueprintReadOnly)
	ATimeManager* TimeManager = nullptr;
};
