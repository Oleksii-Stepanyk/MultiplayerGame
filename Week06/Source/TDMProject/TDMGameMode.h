// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TDMGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TDMPROJECT_API ATDMGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ATDMGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostLogin(APlayerController* NewPlayer) override;

    void ScoreKill(AController* KillerController, AController* VictimController);

protected:
	virtual void BeginPlay() override;

	FTimerHandle MatchTimerHandle;

	void OnMatchTimerTick();
};
