// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBox.h"

// Sets default values
ASpawnBox::ASpawnBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//initialize members
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnBox::BeginPlay()
{
	//schedule first 
	Super::BeginPlay();
	if (ShouldSpawn) {
		ScheduleActorSpawn();
	}

}

void ASpawnBox::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Remove all timers associated with this object instance
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	//GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandler);

}

// Called every frame
void ASpawnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawnBox::SpawnActor()
{
	//
	bool SpawnedActor = false;
	if (ActorClassToBeSpawned) {
		//calculate the bounds of the box

		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		//compute a random position withn the box bounds
		FVector SpawnLocation = BoxBounds.Origin;
		SpawnLocation.X += BoxBounds.BoxExtent.X * (2 * FMath::FRand() - 1);
		SpawnLocation.Y += BoxBounds.BoxExtent.Y * (2 * FMath::FRand() - 1);
		SpawnLocation.Z += BoxBounds.BoxExtent.Z * (2 * FMath::FRand() - 1);
		//SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();

		//Spawn the actor
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;

	}
	return SpawnedActor;
}

void ASpawnBox::EnableActorSpawing(bool Enable)
{
	//update the ShouldSpawn state
	ShouldSpawn = Enable;

	//check which timer action should be done
	if (Enable) {
		ScheduleActorSpawn();
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandler);
	}
}

void ASpawnBox::ScheduleActorSpawn()
{
	//1. COmpute time offset to spawn
	float DeltaToNextSpawn = AvgSpawnTime + (RandomSpawnTimeOffset * (2 * FMath::FRand() - 1));

	//2. Schedule spawning 
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandler, this, &ASpawnBox::ReScheduleActorSpawn, DeltaToNextSpawn, false);
}

void ASpawnBox::ReScheduleActorSpawn()
{
	if (SpawnActor()) {
		if (ShouldSpawn) {
			ScheduleActorSpawn();
		}
	}
	else {
		// TODO: log the error
	}
}

