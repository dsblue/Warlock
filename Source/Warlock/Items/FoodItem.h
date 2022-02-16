// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class WARLOCK_API UFoodItem : public UItem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	float HealAmount = 10;

	void Use(class AWarlockCharacter* Character);
};
