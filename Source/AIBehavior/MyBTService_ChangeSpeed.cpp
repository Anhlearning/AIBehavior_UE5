// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_ChangeSpeed.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCAIController.h"
#include "NPC.h"
#include "GameFramework/CharacterMovementComponent.h"
UMyBTService_ChangeSpeed::UMyBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Change Speed";
}

void UMyBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {
		if (auto* const NPC = Cast<ANPC>(cont->GetPawn())) {
			NPC->GetCharacterMovement()->MaxWalkSpeed = SpeedChange;

		}
	}
}
