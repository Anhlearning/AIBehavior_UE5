// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_CheckPlayerFacing.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"
#include "NPCAIController.h"
#include "Math/Vector.h"
UMyBTDecorator_CheckPlayerFacing::UMyBTDecorator_CheckPlayerFacing()
{
	NodeName = "Check Player Facing";
}

bool UMyBTDecorator_CheckPlayerFacing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	auto* const pawn = Cast<ANPC>(cont->GetPawn());
	if (player && pawn) {
		FVector playerForward = player->GetActorForwardVector();
		FVector ToEnemy = (pawn->GetActorLocation() - player->GetActorLocation()).GetSafeNormal();

		float dot = FVector::DotProduct(playerForward, ToEnemy);
		return dot < accpectAngleDot;	
	}

	return false;
}
