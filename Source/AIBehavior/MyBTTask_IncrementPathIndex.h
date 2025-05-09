// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_IncrementPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
public:
	explicit UMyBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	enum class EDirectionType{Forward, Reverse};

	EDirectionType Direction = EDirectionType::Forward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		bool bBiDirectional = false;
};
