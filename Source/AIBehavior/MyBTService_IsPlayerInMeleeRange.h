// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_IsPlayerInMeleeRange.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTService_IsPlayerInMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UMyBTService_IsPlayerInMeleeRange();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BloackBoard", meta = (AllowPrivateAccess = "true"))
	float isDistanceAcceptalbe = 80.f;
};
