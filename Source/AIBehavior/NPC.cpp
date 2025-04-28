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

    Shield = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("SHIELD MESH"));
    Shield->SetupAttachment(GetMesh(), FName("hand_l_socket"));
}

UBehaviorTree* ANPC::GetBehaviorTree() const
{
	return Tree;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
    UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
    if (pAnimInst) {
        pAnimInst->OnPlayMontageNotifyBegin.AddDynamic(this,&ANPC::HandleOnMontageNotifyBegin);
    }
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
    if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackComboMontage))
    {
        isAttacking = true;
        APawn* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (player) {
            FVector dir = player->GetActorLocation() - this->GetActorLocation();
            dir.Z = 0.0f;
            FRotator newRotate = dir.Rotation();
            SetActorRotation(newRotate);
            if (AttackComboMontage && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackComboMontage))
            {
                UE_LOG(LogTemp, Warning, TEXT("BroadCast Anim AttackCombo"));
                currentAnimMontage = AttackComboMontage;
                PlayAnimMontage(AttackComboMontage);
            }
        }
    }
    if(isAttacking) {
        attackCurrentIndex = 1;
    }
     return 0;
}

int ANPC::HeavyAttack_Implementation()
{   
    if (!isAttacking) {
        isAttacking = true;
        APawn* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (player) {
            FVector dir = player->GetActorLocation() - this->GetActorLocation();
            dir.Z = 0.0f;
            FRotator newRotate = dir.Rotation();
            SetActorRotation(newRotate);
        }
        if (AttackHeavyMontage)
        {
            currentAnimMontage = AttackHeavyMontage;
            PlayAnimMontage(AttackHeavyMontage);
        }
    }
    return 0;
}

int ANPC::CounterAttack_Implementation()
{
    if (!isAttacking) {
        isAttacking = true;
        APawn* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (player) {
            FVector dir = player->GetActorLocation() - this->GetActorLocation();
            dir.Z = 0.0f;
            FRotator newRotate = dir.Rotation();
            SetActorRotation(newRotate);
        }
        if (AttackCounterMontage)
        {
            currentAnimMontage = AttackCounterMontage;
            PlayAnimMontage(AttackCounterMontage);
        }
    }
    return 0;
}

int ANPC::ShieldAttack_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("%d %d"), isShielAttack, isAttacking);
    if (!isShielAttack && !isAttacking) {
        isShielAttack = true;
        isAttacking = true;
        APawn* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        if (player) {
            FVector dir = player->GetActorLocation() - this->GetActorLocation();
            dir.Z = 0.0f;
            FRotator newRotate = dir.Rotation();
            SetActorRotation(newRotate);
        }
        if (ShieldAttackMontage)
        {
            UE_LOG(LogTemp, Warning, TEXT("SHIELD COMBO"));
            ACharacterBase* CharPlayer = Cast<ACharacterBase>(player);
            CharPlayer->isDefense = false;
            currentAnimMontage = ShieldAttackMontage;
            PlayAnimMontage(ShieldAttackMontage);
        }
    }

    return 0;
}

void ANPC::DodgeState_Implementation()
{
    isDodging = true;
    wasHitDuringDodge = false;
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
            dodgeAngleOffset = randomAngle;
        }
        else
        {
            dodgeDirection = GetActorRightVector();
            dodgeAngleOffset = -randomAngle;    
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

void ANPC::HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayLoad)
{

    
    attackCurrentIndex --;
    if (attackCurrentIndex < 0) {
        UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
        if (pAnimInst)
        {
            UE_LOG(LogTemp, Warning, TEXT("STOP MONTAGE"));
            isAttacking = false;
            pAnimInst->Montage_Stop(0.4f, AttackComboMontage);

        }
    }
    
}

