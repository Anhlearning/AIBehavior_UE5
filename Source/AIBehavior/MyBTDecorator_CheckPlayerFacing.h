// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_CheckPlayerFacing.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTDecorator_CheckPlayerFacing : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
    UMyBTDecorator_CheckPlayerFacing();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
    UPROPERTY(EditAnywhere, Category = "Dodge")
    float accpectAngleDot = -0.5f;
};
