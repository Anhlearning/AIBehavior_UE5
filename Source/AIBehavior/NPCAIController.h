// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController.h"
#include "NPCAIController.generated.h" 



/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
public : 
	ANPCAIController(FObjectInitializer const& ObjectInitialiler);
protected : 
	virtual void OnPossess(APawn* InPawn) override;
private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;
	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);
};
