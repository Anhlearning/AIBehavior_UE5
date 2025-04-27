// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Teleport.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC.h"
#include "NPCAIController.h"
#include "Kismet/GameplayStatics.h"
UMyBTTask_Teleport::UMyBTTask_Teleport(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "TelePort";
}
EBTNodeResult::Type UMyBTTask_Teleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
    auto* const NPC = Cast<ANPC>(cont->GetPawn());

    if (!cont || !NPC)
    {
        UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Controller or NPC is nullptr!"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Starting teleport check..."));

    if (NPC->wasHitDuringDodge || NPC->isDodging)
    {
        UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Cannot teleport: was hit during dodge or is currently dodging."));
        NPC->wasHitDuringDodge = false;
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    if (CheckMontageIsStoped(NPC))
    {
        UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Montage is already stopped - skipping teleport."));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!Player)
    {
        UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Player not found!"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return EBTNodeResult::Failed;
    }

    FVector playerLocation = Player->GetActorLocation();
    FVector playerBackward = -Player->GetActorForwardVector();
    FVector teleportLocation = playerLocation + (playerBackward * teleportDistance);
    FRotator lookAtRotation = (playerLocation - teleportLocation).Rotation();

    UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Teleporting to Location: %s, Rotation: %s"),
        *teleportLocation.ToString(), *lookAtRotation.ToString());

    NPC->wasHitDuringDodge = false;
    NPC->SetActorLocationAndRotation(teleportLocation, lookAtRotation, false, nullptr, ETeleportType::TeleportPhysics);

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    UE_LOG(LogTemp, Warning, TEXT("[TeleportTask] Teleport success."));
    return EBTNodeResult::Succeeded;
}


bool UMyBTTask_Teleport::CheckMontageIsStoped(ANPC* npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetAnimMontage());
}
