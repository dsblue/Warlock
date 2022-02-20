// Fill out your copyright notice in the Description page of Project Settings.


#include "APickup.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Make a root component for our Actor
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// Tutorial said to set: FAttachmentTransformRules::SnapToTargetNotIncludingScale using the following code
	//   Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// but the runtime suggested to use SetupAttachemt instead, as rule is always Relative
	Mesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	CollisionBox->SetGenerateOverlapEvents(true);
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerEnterPickupBox);
	
	CollisionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy: Actor: %s Comp: %s"), *OtherActor->GetName(), *OtherComp->GetName())
		Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("PickupTriggered: Actor: %s Comp: %s"), *OtherActor->GetName(), *OtherComp->GetName())
}

