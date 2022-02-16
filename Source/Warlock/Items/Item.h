// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryComponent.h"
#include "../WarlockCharacter.h"
#include "Item.generated.h"

/**
 * Abstract Data class describing items the player can own in inventory
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class WARLOCK_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem() {};

	virtual class UWorld* GetWorld() const { return World; }

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Items")
	FText UseItemText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Items")
	class UStaticMesh* PickupItemMesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Items")
	class UTexture2D* Thumbnail;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Items")
	FText ItemDisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Items", meta = (Multiline = "true"))
	FText ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Items", meta = (ClampMin = 0.0f))
	float Weight;

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	virtual void Use(class AWarlockCharacter* character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AWarlockCharacter* character);

};
