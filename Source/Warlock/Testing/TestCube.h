// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestCube.generated.h"

UCLASS(Blueprintable, BlueprintType)
class WARLOCK_API ATestCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
