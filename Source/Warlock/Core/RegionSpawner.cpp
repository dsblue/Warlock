// Fill out your copyright notice in the Description page of Project Settings.


#include "RegionSpawner.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ARegionSpawner::ARegionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Called when the game starts or when spawned
	Region = CreateDefaultSubobject<UBoxComponent>(TEXT("Region"));
	Region->SetupAttachment(RootComponent);
}

void ARegionSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ARegionSpawner::Spawn()
{
	if (ActorToSpawn)
	{
		const FVector Position = UKismetMathLibrary::RandomPointInBoundingBox(Region->GetComponentLocation(), Region->GetScaledBoxExtent());
		const FRotator Rotation = GetActorRotation();

		AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FTransform(Rotation, Position));

		if (Actor != nullptr)
		{
			Actor->OnDestroyed.AddDynamic(this, &ARegionSpawner::OnSpawnedActorDestroyed);
			Spawned.Add(Actor);
			NumSpawned++;
		}
	}
}

void ARegionSpawner::OnSpawnedActorDestroyed(AActor* DestroyedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawner: %s Destoyed: %s"), *this->GetName(), *DestroyedActor->GetName())

	if (NumSpawned > 0)
		NumSpawned--;

	Spawned.Remove(DestroyedActor);
}

// Called every frame
void ARegionSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NumSpawned < Quantity)
	{
		Spawn();
	}
}

