// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SWORD MESH"));
    Sword->SetupAttachment(GetMesh(),FName("hand_r_socket"));
}

UBehaviorTree* ANPC::GetBehaviorTree() const
{
	return Tree;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AAPatrolPath* ANPC::GetPatrolPath()
{
	return PatrolPath;
}

UAnimMontage* ANPC::GetAnimMontage()
{

	return currentAnimMontage;
}
int ANPC::MeleeAttack_Implementation()
{
    // tinh toan combo 
    isAttacking = true;
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastAttackTime > ComboMaxInterval)
    {
        UE_LOG(LogTemp, Error, TEXT("Qua thoi gian nen reset"));
        attackCurrentIndex = 0;
    }
    else
    {
        attackCurrentIndex = (attackCurrentIndex + 1);
    }
    attackCurrentIndex = attackCurrentIndex >= 3 ? attackCurrentIndex = 0 : attackCurrentIndex;
    LastAttackTime = CurrentTime;
    APawn* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (player) {
        FVector dir = player->GetActorLocation() - this->GetActorLocation();
        dir.Z = 0.0f;
        FRotator newRotate = dir.Rotation();
        SetActorRotation(newRotate);
    }
    if (Montages.IsValidIndex(attackCurrentIndex) && Montages[attackCurrentIndex])
    {
        UE_LOG(LogTemp, Error, TEXT("Current Index hien tai la: %d"), attackCurrentIndex);
        currentAnimMontage = Montages[attackCurrentIndex];
        PlayAnimMontage(Montages[attackCurrentIndex]);
    }
	return 0;
}

int ANPC::HeavyAttack_Implementation()
{
    isAttacking = true;
    attackCurrentIndex = 3;
    APawn* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (player) {
        FVector dir = player->GetActorLocation() - this->GetActorLocation();
        dir.Z = 0.0f;
        FRotator newRotate = dir.Rotation();
        SetActorRotation(newRotate);
    }
    if (Montages.IsValidIndex(attackCurrentIndex) && Montages[attackCurrentIndex])
    {
        UE_LOG(LogTemp, Error, TEXT("HEAVY STACK"));
        currentAnimMontage = Montages[attackCurrentIndex];
        PlayAnimMontage(Montages[attackCurrentIndex]);
    }
    return 0;
}

int ANPC::CounterAttack_Implementation()
{
    return 0;
}

int ANPC::ShieldAttack_Implementation()
{
    return 0;
}

void ANPC::DodgeState_Implementation()
{
    isDodging = true;
    wasHitDuringDodge = false;
    attackCurrentIndex = 4;
    FVector playerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
    FVector npcLocation = GetActorLocation();
    FVector directionToPlayer = (playerLocation - npcLocation).GetSafeNormal();
    FVector dodgeDirection = FVector::ZeroVector;
    float dodgeAngleOffset = 0.f;
    if (FVector::DotProduct(directionToPlayer, GetActorForwardVector()) > 0)
    {
        float randomChoice = FMath::RandRange(0.f, 1.f);
        float randomAngle = FMath::FRandRange(10.f, 15.f);
        if (randomChoice < 0.5f)
        {
            dodgeDirection = -GetActorRightVector();
            dodgeAngleOffset = -randomAngle;
        }
        else
        {
            dodgeDirection = GetActorRightVector();
            dodgeAngleOffset = randomAngle;
        }
    }
    dodgeDirection.Normalize();
    FRotator dodgeRotation = dodgeDirection.Rotation();

    dodgeRotation.Yaw += dodgeAngleOffset;

    SetActorRotation(dodgeRotation);

    if (DodgeMontage)
    {
        currentAnimMontage = DodgeMontage;
        PlayAnimMontage(DodgeMontage);
    }
}

