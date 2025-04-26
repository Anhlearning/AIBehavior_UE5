// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_CheckLostTime.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTDecorator_CheckLostTime : public UBTDecorator_BlackboardBase
{
    GENERATED_BODY()

public:
    UMyBTDecorator_CheckLostTime();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition", meta = (ExposeOnSpawn = "true"))
    float LostDuration = 5.f;


	
};
