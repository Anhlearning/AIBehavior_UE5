// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Combat_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombat_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AIBEHAVIOR_API ICombat_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Combat")
	int MeleeAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int HeavyAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int CounterAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int ShieldAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void DodgeState();

};
