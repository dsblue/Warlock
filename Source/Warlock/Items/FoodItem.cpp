// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"
#include "../WarlockCharacter.h"

void UFoodItem::Use(AWarlockCharacter* Character)
{
	Character->Health += HealAmount;

	if (OwningInventory)
	{
		OwningInventory->RemoveItem(this);
	}
}