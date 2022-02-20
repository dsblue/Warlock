// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegionSpawner.generated.h"

UENUM(BlueprintType)
enum class ESpawnRules : uint8
{
	Random,
	RandomAlignVertical,
	RandomAlighHorizontal,
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

	UPROPERTY(EditAnywhere, Category = "Region Spawer", meta = (ClampMin = 0.0f))
	float UpdateRateInSeconds = 0;

	UPROPERTY(EditAnywhere, Category = "Region Spawer")
	bool bUpdateAllAtOnce = true;

	UPROPERTY(EditAnywhere, Category = "Region Spawer")
	bool bRespawnWhenNeeded = true;

	UFUNCTION()
	void OnSpawnedActorDestroyed(AActor* DestroyedActor);

	UPROPERTY(EditAnywhere, Category = "Region Spawer")
	ESpawnRules HowToSpawn = ESpawnRules::Random;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<class AActor*> Spawned;

	FTimerHandle MemberTimerHandle;

	void InternalUpdate();

	int CurrSpawned = 0;

	int TotalSpawned = 0;

	void Spawn();

};
