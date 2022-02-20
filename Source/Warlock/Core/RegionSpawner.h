// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegionSpawner.generated.h"

UCLASS(Blueprintable, BlueprintType)
class WARLOCK_API ACube : public AActor
{
	GENERATED_BODY()

public:
	ACube() 
	{
		// Create a static mesh component
		UStaticMeshComponent* cubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

		// Load the Cube mesh
		UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;

		// Set the component's mesh
		cubeMeshComponent->SetStaticMesh(cubeMesh);

		// Set as root component
		RootComponent = cubeMeshComponent;
	};

};



UCLASS()
class WARLOCK_API ARegionSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARegionSpawner();

protected:
	
	class USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Region Spawer")
	class UBoxComponent* Region;

	UPROPERTY(EditAnywhere, Category = "Region Spawer")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Region Spawer", meta = (ClampMin = 0.0f))
	int32 Quantity = 0;

	UFUNCTION()
	void OnSpawnedActorDestroyed(AActor* DestroyedActor);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<class AActor*> Spawned;

	int NumSpawned = 0;

	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
