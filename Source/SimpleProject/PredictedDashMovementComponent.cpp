// Fill out your copyright notice in the Description page of Project Settings.


#include "PredictedDashMovementComponent.h"
#include "GameFramework/Character.h"

void FSavedMove_Dash::Clear() {
	Super::Clear();

	bWantsToDashSaved = false;
}

uint8 FSavedMove_Dash::GetCompressedFlags() const {
	uint8 Result = Super::GetCompressedFlags();

	if (bWantsToDashSaved) {
		Result |= FLAG_Reserved_1;
	}
	
	return Result;
}

void FSavedMove_Dash::PrepMoveFor(ACharacter* Character) {
	Super::PrepMoveFor(Character);

	UPredictedDashMovementComponent* CharacterMovement = Cast<UPredictedDashMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement) {
		CharacterMovement->bWantsToDash = bWantsToDashSaved;
	}
}

bool FSavedMove_Dash::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const {
	FSavedMove_Dash* NewMovePtr = static_cast<FSavedMove_Dash*>(NewMove.Get());

	if (bWantsToDashSaved != NewMovePtr->bWantsToDashSaved)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void FSavedMove_Dash::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UPredictedDashMovementComponent* CharacterMovement = Cast<UPredictedDashMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		bWantsToDashSaved = CharacterMovement->bWantsToDash;
	}
}

FDashNetworkPredictionData_Client::FDashNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{
}

FSavedMovePtr FDashNetworkPredictionData_Client::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_Dash());
}

UPredictedDashMovementComponent::UPredictedDashMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UPredictedDashMovementComponent::CanDash() const
{
	if (GetWorld())
	{
		bool isWalking = MovementMode == MOVE_Walking;
		bool cooldownPassed = (GetWorld()->GetTimeSeconds() - LastDashTime) >= DashCooldown;
		return isWalking && cooldownPassed;
	}
	return false;
}

FNetworkPredictionData_Client* UPredictedDashMovementComponent::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		UPredictedDashMovementComponent* MutableThis = const_cast<UPredictedDashMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FDashNetworkPredictionData_Client(*this);
	}
	return ClientPredictionData;
}

void UPredictedDashMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);
	bWantsToDash = (Flags & FSavedMove_Character::FLAG_Reserved_1) != 0;
}

void UPredictedDashMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (bWantsToDash)
	{
		bWantsToDash = false;

		LastDashTime = GetWorld()->GetTimeSeconds();

		if (CharacterOwner)
		{
			float DashStrength = 4000.f;
			FVector DashDirection = CharacterOwner->GetActorForwardVector();

			Velocity += DashDirection * DashStrength;
		}
	}
}