// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Dodge.h"
#include "NPC.h"
#include "NPCAIController.h"
#include "Combat_Interface.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_Dodge::UMyBTTask_Dodge(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Dodge State";
}

EBTNodeResult::Type UMyBTTask_Dodge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	auto* const npc = Cast<ANPC>(cont->GetPawn());
	if (auto* const combat = Cast<ICombat_Interface>(npc)) {
		if (CheckMontageIsStoped(npc)) {
			combat->Execute_DodgeState(npc);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

bool UMyBTTask_Dodge::CheckMontageIsStoped(ANPC* npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetAnimMontage());
}
