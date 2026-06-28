// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}

void UHealthComponent::OnHealthUpdate()
{
	APawn* owner = Cast<APawn>(GetOwner());

	//Client-specific functionality
	if (owner && owner->IsLocallyControlled())
	{
		FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

		if (CurrentHealth <= 0)
		{
			FString deathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
		}
	}

	//Server-specific functionality
	if (owner && owner->HasAuthority())
	{
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}
}

void UHealthComponent::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

bool UHealthComponent::ServerApplyDamage_Validate(float damage) {
	bool isValid = (damage > 0) && (damage <= MaxHealth);
	if (!isValid) {
		UE_LOG(LogTemp, Warning, TEXT("Rejected invalid damage: %f"), damage);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Applying valid damage: %f"), damage);
	}
	return isValid;
}

void UHealthComponent::ServerApplyDamage_Implementation(float damage) {
	CurrentHealth = CurrentHealth - damage;
	if (CurrentHealth < 0.0f) {
		CurrentHealth = 0.0f;
	}
	OnHealthUpdate();
	MulticastDamageFlash();
}

void UHealthComponent::MulticastDamageFlash_Implementation()
{
	OnDamageFlash.Broadcast();
}