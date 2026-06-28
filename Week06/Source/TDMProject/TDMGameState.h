// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TDMGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamScoresUpdated, const TArray<int32>&, NewScores);

/**
 * 
 */
UCLASS()
class TDMPROJECT_API ATDMGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
    FOnTeamScoresUpdated OnTeamScoresUpdated;

	void DecreaseRemainingMatchTime(float DeltaTime);

	float GetRemainingMatchTime() const { return RemainingMatchTime; }

	UPROPERTY(ReplicatedUsing = OnRep_RemainingMatchTime)
	float RemainingMatchTime;

	UPROPERTY(ReplicatedUsing = OnRep_TeamScores)
	TArray<int32> TeamScores;

protected:
	virtual void BeginPlay() override;
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_RemainingMatchTime();

	UFUNCTION()
	void OnRep_TeamScores();
};
