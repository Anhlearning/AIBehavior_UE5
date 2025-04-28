// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimShieldAttackState.h"
#include "CharacterBase.h"

void UMyAnimShieldAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner()) {
		if (ACharacterBase* const character = Cast<ACharacterBase>(MeshComp->GetOwner())) {
			character->ShieldAttackStart();
		}
	}
}

void UMyAnimShieldAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner()) {
		if (ACharacterBase* const character = Cast<ACharacterBase>(MeshComp->GetOwner())) {
			character->ShieldAttackEnd();
		}
	}
}
