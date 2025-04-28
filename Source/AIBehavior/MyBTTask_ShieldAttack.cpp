// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ShieldAttack.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBase.h"
UMyBTTask_ShieldAttack::UMyBTTask_ShieldAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Shield Attack";
}

EBTNodeResult::Type UMyBTTask_ShieldAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const outOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (outOfRange) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {
		auto* const NPC = Cast<ANPC>(cont->GetPawn());
		auto* const characterBase = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		auto* const enemyBase = Cast<ACharacter>(NPC);
		if (!characterBase->isDefense) {
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}
		if (auto* const icombat = Cast<ICombat_Interface>(NPC)) {
			if (CheckMontageIsStoped(NPC)) {
				icombat->Execute_ShieldAttack(NPC);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Type();
}

bool UMyBTTask_ShieldAttack::CheckMontageIsStoped(ANPC* npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetAnimMontage());
}
