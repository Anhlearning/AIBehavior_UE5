// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APatrolPath.generated.h"

UCLASS()
class AIBEHAVIOR_API AAPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAPatrolPath();
	int GetLengthPatrol();
	FVector GetPosFromIndexPatrol(int index);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoints", meta = (MakeEditWidget="true", AllowPrivateAccess = "true"))
	TArray<FVector> PatrolPosVector;
};
