// Fill out your copyright notice in the Description page of Project Settings.


#include "APatrolPath.h"

// Sets default values
AAPatrolPath::AAPatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

int AAPatrolPath::GetLengthPatrol()
{
	return PatrolPosVector.Num();
}

FVector AAPatrolPath::GetPosFromIndexPatrol(int index)
{
	return PatrolPosVector[index];
}



