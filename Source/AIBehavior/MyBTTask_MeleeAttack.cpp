// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MeleeAttack.h"
#include "NPC.h"
#include "NPCAIController.h"
#include "Combat_Interface.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_MeleeAttack::UMyBTTask_MeleeAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Melee Attack";
}

EBTNodeResult::Type UMyBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const outOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (outOfRange) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	auto const* cont = OwnerComp.GetAIOwner();
	auto const pawn = Cast<ANPC>(cont->GetPawn());

	if (auto* const icombat = Cast<ICombat_Interface>(pawn)) {
		if (CheckMontageIsStoped(pawn)) {
			icombat->Execute_MeleeAttack(pawn);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

bool UMyBTTask_MeleeAttack::CheckMontageIsStoped(ANPC* npc)
{
	if (npc->GetAnimMontage() == npc->AttackComboMontage) {
		return true;
	}
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetAnimMontage());
}

