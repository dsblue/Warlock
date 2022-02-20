// Fill out your copyright notice in the Description page of Project Settings.


#include "RegionSpawner.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ARegionSpawner::ARegionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Called when the game starts or when spawned
	Region = CreateDefaultSubobject<UBoxComponent>(TEXT("Region"));
	Region->SetupAttachment(RootComponent);
}

void ARegionSpawner::BeginPlay()
{
	Super::BeginPlay();

	verify(Quantity >= 0);

	InternalUpdate();

	if (UpdateRateInSeconds)
	{
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARegionSpawner::InternalUpdate, UpdateRateInSeconds, true);
	}
}

void ARegionSpawner::Spawn()
{
	if (ActorToSpawn)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = GetActorRotation();

		FVector RandPosition = FMath::RandPointInBox(
			FBox::BuildAABB(Region->GetComponentLocation(), Region->GetScaledBoxExtent())
		);

		switch (HowToSpawn)
		{
			case ESpawnRules::Random:
				Location = RandPosition;
				break;
			case ESpawnRules::RandomAlighHorizontal:
				Location = RandPosition;
				Location.Z = GetActorLocation().Z;
				break;
			case ESpawnRules::RandomAlignVertical:
				Location = RandPosition;
				Location.X = GetActorLocation().X;
				break;
			default:
				checkNoEntry()
				break;
		}
		
		AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FTransform(Rotation, Location));

		if (Actor != nullptr)
		{
			Actor->OnDestroyed.AddDynamic(this, &ARegionSpawner::OnSpawnedActorDestroyed);
			Spawned.Add(Actor);
			CurrSpawned++;
			TotalSpawned++;
		}
	}
}

void ARegionSpawner::InternalUpdate()
{
	do
	{
		Spawn();
	}
	while ((CurrSpawned < Quantity) && bUpdateAllAtOnce);

	if (!bRespawnWhenNeeded && (Quantity <= TotalSpawned))
	{
		GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	}
}

void ARegionSpawner::OnSpawnedActorDestroyed(AActor* DestroyedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawner: %s Destoyed: %s"), *this->GetName(), *DestroyedActor->GetName())

	if (CurrSpawned > 0)
		CurrSpawned--;

	Spawned.Remove(DestroyedActor);
}

