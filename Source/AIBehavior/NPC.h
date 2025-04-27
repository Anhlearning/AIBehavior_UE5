// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "APatrolPath.h"
#include "Animation/AnimMontage.h"
#include "CharacterBase.h"
#include "Combat_Interface.h"
#include "NPC.generated.h"
UCLASS()
class AIBEHAVIOR_API ANPC : public ACharacterBase,public ICombat_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	UBehaviorTree* GetBehaviorTree() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess=""))
	UBehaviorTree* Tree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = ""))
	AAPatrolPath* PatrolPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = ""))
	TArray<UAnimMontage*> Montages;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = ""))
	UAnimMontage* DodgeMontage;
	UAnimMontage* currentAnimMontage;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	AAPatrolPath* GetPatrolPath();
	UAnimMontage* GetAnimMontage();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = ""))
	UStaticMeshComponent* Sword;
	virtual int MeleeAttack_Implementation() override;
	virtual int HeavyAttack_Implementation() override;
	virtual int CounterAttack_Implementation() override;
	virtual int ShieldAttack_Implementation() override;
	virtual void DodgeState_Implementation() override;
	float LastAttackTime = 0.f;
	float ComboMaxInterval = 1.8f;
};
