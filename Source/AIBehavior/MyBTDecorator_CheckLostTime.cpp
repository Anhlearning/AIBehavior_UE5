// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_CheckLostTime.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTDecorator_CheckLostTime::UMyBTDecorator_CheckLostTime()
{
	NodeName = "Has Lost Player";
}

bool UMyBTDecorator_CheckLostTime::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    float LostTime = BB->GetValueAsFloat("LastLostSightTime");
    float CurrentTime = OwnerComp.GetWorld()->GetTimeSeconds();

    return (CurrentTime - LostTime) >= LostDuration;
}
