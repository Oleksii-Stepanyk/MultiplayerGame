// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMGameState.h"
#include "Net/UnrealNetwork.h"

void ATDMGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TeamScores.Init(0, 2);
		RemainingMatchTime = 60.0f;
	}
}

void ATDMGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATDMGameState, RemainingMatchTime);
	DOREPLIFETIME(ATDMGameState, TeamScores);
}

void ATDMGameState::OnRep_RemainingMatchTime()
{
	// Handle remaining match time replication
}

void ATDMGameState::OnRep_TeamScores()
{
	OnTeamScoresUpdated.Broadcast(TeamScores);
}

void ATDMGameState::DecreaseRemainingMatchTime(float DeltaTime)
{
	if (HasAuthority())
	{
		RemainingMatchTime -= DeltaTime;
		if (RemainingMatchTime < 0.0f)
		{
			RemainingMatchTime = 0.0f;
		}
	}
}