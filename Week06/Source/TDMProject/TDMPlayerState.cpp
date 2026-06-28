// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMPlayerState.h"
#include "Net/UnrealNetwork.h"

ATDMPlayerState::ATDMPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ATDMPlayerState::BeginPlay()
{
	Super::BeginPlay();

	TeamID = 255; // Default team ID (No team)
	Kills = 0;
	Deaths = 0;
}

void ATDMPlayerState::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATDMPlayerState, TeamID);
	DOREPLIFETIME(ATDMPlayerState, Kills);
	DOREPLIFETIME(ATDMPlayerState, Deaths);
}

void ATDMPlayerState::OnRep_TeamID()
{
	// Handle team ID replication
}

void ATDMPlayerState::OnRep_Kills()
{
	// Handle kills replication
}

void ATDMPlayerState::OnRep_Deaths()
{
	// Handle deaths replication
}