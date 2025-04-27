// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_HeavyAttack.h"
#include "NPC.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat_Interface.h"

UMyBTTask_HeavyAttack::UMyBTTask_HeavyAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Heavy Attack";
}

EBTNodeResult::Type UMyBTTask_HeavyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const isOutRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (isOutRange) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {
		auto* const npc = Cast<ANPC>(cont->GetPawn());
		if (auto* const combat = Cast<ICombat_Interface>(npc)) {
			if (CheckMontageIsStoped(npc)) {
				combat->Execute_HeavyAttack(npc);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}

bool UMyBTTask_HeavyAttack::CheckMontageIsStoped(ANPC* npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetAnimMontage());
}
