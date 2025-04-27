// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_UCanDodgeDecorator.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBase.h"
#include "NPCAIController.h"


UMyBTDecorator_UCanDodgeDecorator::UMyBTDecorator_UCanDodgeDecorator()
{
}

bool UMyBTDecorator_UCanDodgeDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	auto* const Player = Cast<ACharacterBase> (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!NPC || !Player) {
		return false;
	}
	FVector playerLocation = Player->GetActorLocation();
	FVector npcLocation = NPC->GetActorLocation();
	float distance = FVector::Dist(playerLocation, npcLocation);
	FVector playerForward = Player->GetActorForwardVector();
	FVector ToEnemy = (NPC->GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();
	if (FVector::DotProduct(playerForward, ToEnemy) > 0) {
		if (distance <= DodgeDistance && Player->isAttacking)
		{
			EAttackType currentAttackType = EAttackType::NormalAttack;
			if (ShouldDodgeAttackType(currentAttackType))
			{
				return true;
			}
		}
	}
	return false;
}

bool UMyBTDecorator_UCanDodgeDecorator::ShouldDodgeAttackType(EAttackType AttackType) const
{
	return AttackType == EAttackType::NormalAttack;
}
