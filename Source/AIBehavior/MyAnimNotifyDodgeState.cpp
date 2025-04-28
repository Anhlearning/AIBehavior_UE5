// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyDodgeState.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBase.h"
#include "NPC.h"
#include "Combat_Interface.h"
void UMyAnimNotifyDodgeState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	/*if (MeshComp && MeshComp->GetOwner()) {
		if (ACharacterBase* const character = Cast<ACharacterBase>(MeshComp->GetOwner())) {
			character->isDodging=true;
			character->wasHitDuringDodge = false;
		}
	}*/
}

void UMyAnimNotifyDodgeState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        if (ANPC* const character = Cast<ANPC>(MeshComp->GetOwner()))
        {
            character->isDodging = false;
            if (!character->wasHitDuringDodge)
            {
                UWorld* World = MeshComp->GetWorld(); 
                if (World)
                {
                    auto* const Player = UGameplayStatics::GetPlayerCharacter(World, 0);
                    if (Player)
                    {
                        FVector playerLocation = Player->GetActorLocation();
                        FVector playerBackward = -Player->GetActorForwardVector();
                        FVector teleportLocation = playerLocation + (playerBackward * 100.f);
                        FRotator lookAtRotation = (playerLocation - teleportLocation).Rotation();

                        UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Teleporting to Location: %s, Rotation: %s"),
                            *teleportLocation.ToString(), *lookAtRotation.ToString());
                        character->SetActorLocationAndRotation(teleportLocation, lookAtRotation, false, nullptr, ETeleportType::TeleportPhysics);
                        if (auto* const Icombat = Cast<ICombat_Interface>(character)) {
                            Icombat->Execute_CounterAttack(character);
                        }
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] World is null!"));
                }
            }
        }
    }
}

