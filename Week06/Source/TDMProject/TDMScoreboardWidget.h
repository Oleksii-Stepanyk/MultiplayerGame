// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "TDMScoreboardRow.h"
#include "TDMScoreboardWidget.generated.h"

/**
 *
 */
UCLASS()
class UTDMScoreboardWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY()
    TArray<class UTDMScoreboardRow*> ScoreRows;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* ScoreList;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MatchTimerText;

    // We need to know what row Blueprint to spawn
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UTDMScoreboardRow> RowWidgetClass;

    virtual void NativeConstruct() override;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
