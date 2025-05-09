// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UMyBTTask_MeleeAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	bool CheckMontageIsStoped(ANPC* npc);
};
