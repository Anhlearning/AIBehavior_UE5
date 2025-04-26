// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindPathPointClass.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTTask_FindPathPointClass : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UMyBTTask_FindPathPointClass(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BloackBoard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector PatrolPathVectorKey;
};
