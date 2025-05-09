// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_HeavyAttack.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTTask_HeavyAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public :
	explicit UMyBTTask_HeavyAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	bool CheckMontageIsStoped(ANPC* npc);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float IsRangeAcceptable = 150.f;
};
