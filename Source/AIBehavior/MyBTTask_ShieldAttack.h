// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NPC.h"
#include "MyBTTask_ShieldAttack.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTTask_ShieldAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UMyBTTask_ShieldAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	bool CheckMontageIsStoped(ANPC* npc);

};
