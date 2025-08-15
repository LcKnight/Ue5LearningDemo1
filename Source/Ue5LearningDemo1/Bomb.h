// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DefaultPawn.h"

#include "Bomb.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJumpTriggerSignature, AActor*, OtherActor, UPrimitiveComponent*, OtherComp);


UCLASS()
class UE5LEARNINGDEMO1_API ABomb : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABomb();

	UFUNCTION(BlueprintCallable)
	void Jump(float velocity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when other actor's component hits the collider
	UFUNCTION(BlueprintCallable)
	void OnComponentBeginOverlap(class UBoxComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Livetime = 2.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity = 3.f;


	UPROPERTY(EditAnywhere)
	UClass* TriggerCLass = ADefaultPawn::StaticClass();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Static mesh for rendering
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;


	UPROPERTY(BlueprintAssignable)
	FOnJumpTriggerSignature OnJumpTrigger;





	bool IsLaunched = false;

};
