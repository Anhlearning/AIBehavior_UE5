// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindPathPointClass.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC.h"
#include "NPCAIController.h"
UMyBTTask_FindPathPointClass::UMyBTTask_FindPathPointClass(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Path Point";
}

EBTNodeResult::Type UMyBTTask_FindPathPointClass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {
		if (auto* const bc = OwnerComp.GetBlackboardComponent()) {
			auto const indexKey = bc->GetValueAsInt(GetSelectedBlackboardKey());

			if (auto* const npc = Cast<ANPC>(cont->GetPawn())) {
				auto const Loc = npc->GetPatrolPath()->GetPosFromIndexPatrol(indexKey);

				auto const GlobalLoc = npc->GetPatrolPath()->GetActorTransform().TransformPosition(Loc);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalLoc);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}


	return EBTNodeResult::Failed;
}
