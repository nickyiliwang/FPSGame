// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{

	// Instantiate these sub-object and gave it a name
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	// We don't collision on our objective Mesh object
	// Arrow operator are pointers that assign values to the struct
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	// Customization: no physics, only queries(line tracers, overlap events)
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Channel Setup, ignore all but only respond to player(Pawn) channel
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Overlap here means we want other projectiles to pass-through this object
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	// MeshComp is the Root
	// SphereComp is attached to the RootComp with the arrow syntax
	// Blueprint will show the hierarchy
	SphereComp->SetupAttachment(MeshComp);

	// Reacting to Player touching the Objective Actor
	// Option 1:
	//SphereComp->OnComponentBeginOverlap

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
}

void AFPSObjectiveActor::PlayEffects()
{
	// Since this Objective Actor will be stationary, we spawn at location
	// SpawnEmitterAtLocation(which world are we applying this effect, EmitterTemplate, location)
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());

}


// Implementing reaction to player touching the Objective Actor
//Option 2
// Catch all/ Collects all overlapping events on this Object.
void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();

	// check if we have an character overlap
	// We are casting this actor 
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}
}