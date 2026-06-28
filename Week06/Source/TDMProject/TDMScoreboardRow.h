// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TDMScoreboardRow.generated.h"

/**
 *
 */
UCLASS()
class UTDMScoreboardRow : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamNameText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;

    UPROPERTY()
    int32 CurrentScore = -1;

public:
    void UpdateRow(int32 TeamIndex, int32 NewScore)
    {
        if (TeamNameText)
        {
            FString TeamString = FString::Printf(TEXT("Team %d"), TeamIndex);
            TeamNameText->SetText(FText::FromString(TeamString));
        }

        if (CurrentScore != NewScore)
        {
            CurrentScore = NewScore;

            if (ScoreText)
            {
                ScoreText->SetText(FText::AsNumber(CurrentScore));
            }
        }
    }
};
