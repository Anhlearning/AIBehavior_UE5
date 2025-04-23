// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPCAIController.h"
#include "NavigationSystem.h"
UMyBTTask_FindRandomLocation::UMyBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UMyBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) {// get aiowner
		if (auto* const npc = cont->GetPawn()) {
			auto const origin= npc->GetActorLocation(); // lấy vị trí để làm gốc tọa độ 
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()) /* lấy ra bản đồ của thế giới */ ) {
				FNavLocation loc;
				if (NavSys->GetRandomPointInNavigableRadius(origin, searchRadius, loc)) {// hàm random 
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);// lưu vào key hiện tại set trong Behavior tree 
				}
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}

