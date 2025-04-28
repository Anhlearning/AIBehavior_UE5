// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharacterBase.generated.h"

UCLASS()
class AIBEHAVIOR_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
private :
	bool takeDamage = false;
public:
	// Sets default values for this character's properties
	ACharacterBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called to bind functionality to input
	float GetHealth();
	float GetMaxHealth();
	void SetHealth(float const newHealth);
	bool isAttacking = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY()
	class UWidgetComponent* WidgetComponent;
	float const MaxHealth = 100.f;
	float Health;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Collision",meta=(AllowPrivateAccess="true"))
	class UBoxComponent* RightFistCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* LeftFistCollisionBox;

	UFUNCTION()
	void ShieldAttackStart();
	UFUNCTION()
	void ShieldAttackEnd();

	UFUNCTION()
	void AttackStart();
	UFUNCTION()
	void AttackEnd();
	UFUNCTION()
	void OnAttackOverlapBegin(
		UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComponent,
		int const OtherBodyIndex,
		bool const FromSweep,
		FHitResult const& SweepResult
	);
	UFUNCTION()
	void OnAttackOverlapEnd(
		UPrimitiveComponent* const OverlappedComponent,
		AActor* const otherActor,
		UPrimitiveComponent* const OtherComp,
		int const OtherBodyIndex
	);


	void HitDameReact(AActor* InstigatorController,float const health);
	bool GetIsAttacking();
	int attackCurrentIndex = 0;
	bool isDodging = false;
	bool wasHitDuringDodge = false;
	bool isDefense = false ; 
	bool isShielAttack = false;
};
