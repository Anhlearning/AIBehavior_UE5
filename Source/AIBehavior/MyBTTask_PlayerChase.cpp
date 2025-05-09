// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_PlayerChase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NPC.h"

UMyBTTask_PlayerChase::UMyBTTask_PlayerChase(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Player Chase";
}
EBTNodeResult::Type UMyBTTask_PlayerChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {

		if (auto* const npc = Cast<ANPC>(cont->GetPawn())) {
			if (npc->GetIsAttacking()) {
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		auto const playerLoc = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, playerLoc);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Succeeded;	
}
