// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindPlayerLocation.h"
#include "NPCAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
UMyBTTask_FindPlayerLocation::UMyBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Player Location";
}

EBTNodeResult::Type UMyBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        FVector TargetLocation = Player->GetActorLocation();

        if (searchRandom)
        {
            if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
            {
                FNavLocation RandomLoc;
                if (NavSys->GetRandomPointInNavigableRadius(TargetLocation, radius, RandomLoc))
                {
                    TargetLocation = RandomLoc.Location;
                }
                else
                {
                    FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
                    return EBTNodeResult::Failed;
                }
            }
        }

        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    return EBTNodeResult::Failed;
}
