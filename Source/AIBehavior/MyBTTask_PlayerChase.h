// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_PlayerChase.generated.h"

/**
 * 
 */
UCLASS()

class AIBEHAVIOR_API UMyBTTask_PlayerChase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
private: 
	explicit UMyBTTask_PlayerChase(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
