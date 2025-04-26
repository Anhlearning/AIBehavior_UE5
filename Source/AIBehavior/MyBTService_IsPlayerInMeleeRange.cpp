// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_IsPlayerInMeleeRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NPCAIController.h"
#include "NPC.h"
#include "Engine/World.h"

UMyBTService_IsPlayerInMeleeRange::UMyBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Is Player In MeleeRange";
}

void UMyBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {
		auto* const npc = Cast<ANPC>(cont->GetPawn());
		auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), npc->GetDistanceTo(player) <= isDistanceAcceptalbe);
	}
}
