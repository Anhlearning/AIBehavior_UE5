// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Math/Vector.h"
#include "Components/BoxComponent.h"
#include "AIBehaviorCharacter.h"
#include "NPC.h"
#include "NPCAIController.h"
#include "HealthBarWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase() :
	WidgetComponent{ CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")) },
	Health{ MaxHealth }
{
	RightFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RIGHTBOXCOLLISION"));
	if (RightFistCollisionBox) {
		FAttachmentTransformRules const Rules{
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false
		};
		RightFistCollisionBox->AttachToComponent(GetMesh(), Rules, "hand_r_socket");
		RightFistCollisionBox->SetRelativeLocation(FVector{ -7.f,0.f,0.f });
	}

	LeftFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LEFTBOXCOLLISION"));
	if (LeftFistCollisionBox) {
		FAttachmentTransformRules const Rules{
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false
		};
		LeftFistCollisionBox->AttachToComponent(GetMesh(), Rules, "hand_l_socket");
		LeftFistCollisionBox->SetRelativeLocation(FVector{ -7.f,0.f,0.f });
	}

	

	FVector const origin{ 0.f,0.f,95.f };
	if (WidgetComponent) {
		UE_LOG(LogTemp, Error, TEXT("WidgetComponent"));
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(origin);
		static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass{ TEXT("/Game/UI/BP_HealthBar") };
		if (WidgetClass.Succeeded()) {
			WidgetComponent->SetWidgetClass((WidgetClass.Class));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetComponent is NULL!"));
	}
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	RightFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightFistCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACharacterBase::OnAttackOverlapBegin);
	RightFistCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACharacterBase::OnAttackOverlapEnd);

	LeftFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftFistCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACharacterBase::OnAttackOverlapBegin);
	LeftFistCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACharacterBase::OnAttackOverlapEnd);
}

void ACharacterBase::ShieldAttackStart()
{
	LeftFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LeftFistCollisionBox->SetCollisionProfileName("First");
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(true);
}

void ACharacterBase::ShieldAttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("RESET SHIELD"));
	isShielAttack = false;
	isAttacking = false;
	takeDamage = false;
	LeftFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(false);
}

void ACharacterBase::AttackStart()
{
	RightFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RightFistCollisionBox->SetCollisionProfileName("First");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(true);

	
}

void ACharacterBase::AttackEnd()
{
	isAttacking = false;
	takeDamage = false;
	RightFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);
}

void ACharacterBase::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent, AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (takeDamage) {
		return;
	}
	if (otherActor == this) {
		return;
	}
	auto* const otherChar = Cast<ACharacterBase>(otherActor);
	if (otherChar->isDefense && !this->isShielAttack) {
		return; 
	}

	else if (auto* const Enemy = Cast<ANPC>(otherActor)) {
		if (Enemy->isDodging) {
			Enemy->wasHitDuringDodge = true;
			auto* const EnemyAI = Cast<ANPCAIController>(Enemy->GetController());
			if (EnemyAI) {
				EnemyAI->GetBlackboardComponent()->SetValueAsBool("HitDuring", true);
			}
		}
		auto const newHealth = Enemy->GetHealth() - Enemy->GetMaxHealth() * 0.1f;
		Enemy->HitDameReact(this,newHealth);
		takeDamage = true;
	}
	else {
		auto* const Player = Cast<AAIBehaviorCharacter>(otherActor);
		if (Player) {
			auto const newHealth = Player->GetHealth() - Player->GetMaxHealth() * 0.1f;
			Player->HitDameReact(this,newHealth);
			takeDamage = true;
		}
	}
}

void ACharacterBase::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent, AActor* const otherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex)
{

}

void ACharacterBase::HitDameReact(AActor* InstigatorController,float const health)
{
	
	FVector HitDirection;
	if (InstigatorController)
	{
		FVector KnockbackDirection = GetActorLocation() - InstigatorController->GetActorLocation();
		KnockbackDirection.Z = 0.f; 
		KnockbackDirection.Normalize();

		float KnockbackStrength = 300.f; 

		LaunchCharacter(KnockbackDirection * KnockbackStrength, true, true);
		SetHealth(health);
	}
}

bool ACharacterBase::GetIsAttacking()
{
	return isAttacking;
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (auto const widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject())) {
		widget->SetBarValuePercent(Health / MaxHealth);
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACharacterBase::GetHealth()
{
	return Health;
}

float ACharacterBase::GetMaxHealth()
{
	return MaxHealth;
}

void ACharacterBase::SetHealth(float const newHealth)
{
	Health = newHealth;
	if (auto* const Player = Cast<AAIBehaviorCharacter>(this)) {
		if (Health <= 0.f) {
		}
	}
	else {
	}
}

