// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_UCanDodgeDecorator.generated.h"

/**
 * 
 */
UCLASS()
class AIBEHAVIOR_API UMyBTDecorator_UCanDodgeDecorator : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
    // Constructor
    UMyBTDecorator_UCanDodgeDecorator();

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
    enum class EAttackType {
        HeavyAttack,
        NormalAttack,
    };
private:
    
    UPROPERTY(EditAnywhere, Category = "Dodge")
    float DodgeDistance = 500.f;
    bool ShouldDodgeAttackType(EAttackType AttackType) const;

};
