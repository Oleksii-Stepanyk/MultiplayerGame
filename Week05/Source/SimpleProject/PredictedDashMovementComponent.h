// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PredictedDashMovementComponent.generated.h"

class FSavedMove_Dash : public FSavedMove_Character
{
public:
	typedef FSavedMove_Character Super;

	bool bWantsToDashSaved = false;

	virtual uint8 GetCompressedFlags() const override;
	virtual void PrepMoveFor(ACharacter* Character) override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
	virtual void Clear() override;
};

class FDashNetworkPredictionData_Client : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;
	
	FDashNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement);

	virtual FSavedMovePtr AllocateNewMove() override;
};

UCLASS()
class SIMPLEPROJECT_API UPredictedDashMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UPredictedDashMovementComponent(const FObjectInitializer& ObjectInitializer);

	friend class FSavedMove_Dash;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dashing")
	bool bWantsToDash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dashing")
	float DashCooldown = 1.5f;

	float LastDashTime = -999.0f;

	UFUNCTION(BlueprintCallable, Category = "Dashing")
	virtual bool CanDash() const;

	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

};
