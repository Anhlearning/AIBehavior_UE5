// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "AIBehaviorCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "NPC.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitialiler)
{
	SetupPerceptionSystem();
}

void ANPCAIController::OnPossess(APawn* InPawn) // call when scene start 
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast<ANPC>(InPawn)) { // ép ki?u INPAWN => ANPC 
		if (UBehaviorTree* const tree = npc->GetBehaviorTree()) { // l?y behavior tree ?ã ???c gán trên npc 
			UBlackboardComponent* b; // t?o m?t con tr? BlackBroad
			UseBlackboard(tree->BlackboardAsset, b); // l?y blackBroad có s?n trên tree 
			Blackboard = b; // gán B -> vào con tr?
			RunBehaviorTree(tree);
		}
	}
}

void ANPCAIController::SetupPerceptionSystem()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    if (!SightConfig) return;

    // Tạo và thiết lập perception component
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));

    SightConfig->SightRadius = 800.f;
    SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
    SightConfig->PeripheralVisionAngleDegrees = 90.f;
    SightConfig->SetMaxAge(5.f);
    SightConfig->AutoSuccessRangeFromLastSeenLocation = 850.f;

    // Cho phép phát hiện tất cả các loại đối tượng
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    // Gán giác quan Sight là giác quan chính
    GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());

    // Lắng nghe sự kiện khi phát hiện mục tiêu
    GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetDetected);


    // Đăng ký cấu hình Sight vào perception component
    GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void ANPCAIController::OnTargetDetected(AActor* actor, FAIStimulus Stimulus)
{
    if (auto* const ch = Cast<AAIBehaviorCharacter>(actor)) {
        const bool bSeen = Stimulus.WasSuccessfullySensed();
        GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", bSeen);

        if (!bSeen)
        {
            // Ghi lại thời điểm mất dấu player
            float TimeNow = GetWorld()->GetTimeSeconds();
            GetBlackboardComponent()->SetValueAsFloat("LastLostSightTime", TimeNow);
            GetBlackboardComponent()->SetValueAsVector("LastKnownLocation", actor->GetActorLocation());
        }
    }
}

void ANPCAIController::OnLostTarget()
{
}
