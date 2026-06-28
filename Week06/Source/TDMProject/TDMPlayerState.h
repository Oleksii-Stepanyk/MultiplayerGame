// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TDMPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TDMPROJECT_API ATDMPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATDMPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	int32 GetTeamID() const { return TeamID; }
	int32 GetKills() const { return Kills; }
	int32 GetDeaths() const { return Deaths; }

	void SetTeamID(int32 NewTeamID) { TeamID = NewTeamID; }
	void AddKill() { Kills++; }
	void AddDeath() { Deaths++; }

protected:
	virtual void BeginPlay() override;
	
	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_TeamID)
	int32 TeamID;

	UPROPERTY(ReplicatedUsing = OnRep_Kills)
	int32 Kills;

	UPROPERTY(ReplicatedUsing = OnRep_Deaths)
	int32 Deaths;

protected:
	UFUNCTION()
	void OnRep_TeamID();

	UFUNCTION()
	void OnRep_Kills();

	UFUNCTION()
	void OnRep_Deaths();
};
