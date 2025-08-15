// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "SpawnBox.generated.h"

UCLASS()
class UE5LEARNINGDEMO1_API ASpawnBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when the actor stops playing
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Will spawn an actor of the selected class
	UFUNCTION(BlueprintCallable)
	bool SpawnActor();

	//Actor class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	//change whether the actor should be spawned(current pending spawn will still continue)
	UFUNCTION(BlueprintCallable)
	void EnableActorSpawing(bool Enable);

private:
	//WIll schedule a actor spawn
	UFUNCTION()
	void ScheduleActorSpawn();

	void ReScheduleActorSpawn();
private:

	UPROPERTY(EditAnywhere)
	bool ShouldSpawn = true;

	//Average time between spawns /\No random
	UPROPERTY(EditAnywhere)
	float AvgSpawnTime = 5.0f;

	//Random +/- offset of the spawn time
	UPROPERTY(EditAnywhere)
	float RandomSpawnTimeOffset = 1.0f;


	//Box in which we will spawn the actor
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	//Timer handler to spawn actor
	FTimerHandle SpawnTimerHandler;

};
