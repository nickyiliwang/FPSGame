// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

// like importing packages in js, we are only gonnna import what we need
// the details are gonna be in .cpp file
class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

	// No one outside this class can call functions in here
protected:

	// <Class>* <- this is a pointer to a class

	// UPROP: Exposing these Components to blueprints and have the ability to edit them
	UPROPERTY(VisibleAnywhere, Category = "Components");
	// visually show that the objective exists
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components");
	// holds collision information
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Fn that spawns particle effects, when we overlap with this objective as player
	void PlayEffects();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
