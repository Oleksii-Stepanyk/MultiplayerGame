// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMGameMode.h"
#include "TDMGameState.h"
#include "TDMPlayerState.h"
#include "TDMProjectCharacter.h"
#include "TDMProjectPlayerController.h"

ATDMGameMode::ATDMGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    GameStateClass = ATDMGameState::StaticClass();
    PlayerStateClass = ATDMPlayerState::StaticClass();
    PlayerControllerClass = ATDMProjectPlayerController::StaticClass();

    DefaultPawnClass = ATDMProjectCharacter::StaticClass();

    bDelayedStart = false;
}

void ATDMGameMode::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        MatchTimerHandle,
        this,
        &ATDMGameMode::OnMatchTimerTick,
        1.0f,
        true
    );
}

void ATDMGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    int32 Team0Count = 0;
    int32 Team1Count = 0;

    ATDMGameState* TDMGameState = GetGameState<ATDMGameState>();
    if (TDMGameState)
    {
        for (APlayerState* PS : TDMGameState->PlayerArray)
        {
            ATDMPlayerState* TDMPlayerState = Cast<ATDMPlayerState>(PS);

            if (TDMPlayerState && TDMPlayerState != NewPlayer->GetPlayerState<APlayerState>())
            {
                if (TDMPlayerState->GetTeamID() == 0)
                {
                    Team0Count++;
                }
                else if (TDMPlayerState->GetTeamID() == 1)
                {
                    Team1Count++;
                }
            }
        }
    }

    ATDMPlayerState* NewPlayerState = NewPlayer->GetPlayerState<ATDMPlayerState>();
    if (NewPlayerState)
    {
        if (Team0Count <= Team1Count)
        {
            NewPlayerState->SetTeamID(0);
        }
        else
        {
            NewPlayerState->SetTeamID(1);
        }
    }
}

void ATDMGameMode::OnMatchTimerTick()
{
    ATDMGameState* TDMGameState = GetGameState<ATDMGameState>();
    if (TDMGameState)
    {
        TDMGameState->DecreaseRemainingMatchTime(1.0f);

        if (TDMGameState->GetRemainingMatchTime() <= 0.1f)
        {
            GetWorldTimerManager().ClearTimer(MatchTimerHandle);

            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TIME UP! Match Over!"));
            }

            EndMatch();

            FTimerHandle RestartTimerHandle;
            GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &ATDMGameMode::RestartGame, 5.0f, false);
        }
    }
}

void ATDMGameMode::ScoreKill(AController* KillerController, AController* VictimController)
{
    ATDMGameState* TDMGameState = GetGameState<ATDMGameState>();
    
    ATDMPlayerState* KillerPS = KillerController ? KillerController->GetPlayerState<ATDMPlayerState>() : nullptr;
    ATDMPlayerState* VictimPS = VictimController ? VictimController->GetPlayerState<ATDMPlayerState>() : nullptr;

    if (VictimPS)
    {
        VictimPS->AddDeath();
    }

    if (KillerPS && KillerPS != VictimPS)
    {
        KillerPS->AddKill();

        if (TDMGameState)
        {
            int32 KillerTeam = KillerPS->GetTeamID();
            
            if (TDMGameState->TeamScores.IsValidIndex(KillerTeam))
            {
                TDMGameState->TeamScores[KillerTeam]++;
                if (TDMGameState->TeamScores[KillerTeam] >= 10)
                {
                    if (GEngine)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SCORE LIMIT REACHED! Match Over!"));
                    }

                    EndMatch();

                    FTimerHandle RestartTimerHandle;
                    GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &ATDMGameMode::RestartGame, 5.0f, false);
				}
            }
        }
    }
}