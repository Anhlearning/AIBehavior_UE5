// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_IncrementPathIndex.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC.h"
#include "NPCAIController.h"

UMyBTTask_IncrementPathIndex::UMyBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Increment Path Index";
}

EBTNodeResult::Type UMyBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {
		if (auto* const NPC = Cast<ANPC>(cont->GetPawn())) {
			if (auto* const bc = OwnerComp.GetBlackboardComponent()) {

				auto const size = NPC->GetPatrolPath()->GetLengthPatrol();
				auto const startIndex = 0;
				auto const maxIndex = size - 1;
				auto  indexCurrent = bc->GetValueAsInt(GetSelectedBlackboardKey());

				if (bBiDirectional) {
					if (indexCurrent >= maxIndex && Direction == EDirectionType::Forward) {
						Direction = EDirectionType::Reverse;
					}
					else if (indexCurrent == startIndex && Direction == EDirectionType::Reverse) {
						Direction = EDirectionType::Forward;
					}
				}
				bc->SetValueAsInt(GetSelectedBlackboardKey(), (Direction == EDirectionType::Forward ? ++indexCurrent : --indexCurrent) % size);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}

		}
	}


	return EBTNodeResult::Failed;
}
