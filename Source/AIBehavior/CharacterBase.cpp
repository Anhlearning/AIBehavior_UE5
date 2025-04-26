// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Math/Vector.h"
#include "HealthBarWidget.h"
// Sets default values
ACharacterBase::ACharacterBase() :
	WidgetComponent{ CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")) },
	Health{ MaxHealth }
{
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
}

