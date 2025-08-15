// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

// Sets default values
ABomb::ABomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create the (root) component for rendering
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

void ABomb::Jump(float velocity)
{
	//make sure jump is only executed once
	if (!IsLaunched) {
		// Excute jump using the physics system
		StaticMesh->AddImpulse({ .0f,.0f, velocity * 500.f });

		// Initiate object destruction
		IsLaunched = true;
		SetActorTickEnabled(true);
		//SetActorTickInterval(1.f);

	}
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	//Setup per instance OnComponentOverlap event

	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);


	//Ticking is only required after launching
	SetActorTickEnabled(false);
}

void ABomb::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsLaunched && OtherActor->IsA(TriggerCLass)) {
		OnJumpTrigger.Broadcast(OtherActor, Component);
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsLaunched) {
		//Decrement livetime

		Livetime -= DeltaTime;
		//Check actor destruction
		if (Livetime <= 0.f) {
			Destroy();
		}

	}

}

