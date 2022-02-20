// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCube.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RegionSpawner.generated.h"

// Sets default values
ATestCube::ATestCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a static mesh component
	UStaticMeshComponent* cubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	// Load the Cube mesh
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;

	// Set the component's mesh
	cubeMeshComponent->SetStaticMesh(cubeMesh);

	// Set as root component
	RootComponent = cubeMeshComponent;
}

// Called when the game starts or when spawned
void ATestCube::BeginPlay()
{
	Super::BeginPlay();
	
}
