// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMScoreboardWidget.h"
#include "TDMGameState.h"

void UTDMScoreboardWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UTDMScoreboardWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (ATDMGameState* GS = GetWorld()->GetGameState<ATDMGameState>())
    {
        if (MatchTimerText)
        {
            int32 TotalSeconds = FMath::Max(0, FMath::FloorToInt(GS->GetRemainingMatchTime()));
            int32 Minutes = TotalSeconds / 60;
            int32 Seconds = TotalSeconds % 60;

            FString FormatString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
            MatchTimerText->SetText(FText::FromString(FormatString));
        }

        if (GS->TeamScores.Num() >= 0)
        {
            if (ScoreRows.Num() != GS->TeamScores.Num())
            {
                ScoreList->ClearChildren();
                ScoreRows.Empty();

                for (int32 i = 0; i < GS->TeamScores.Num(); i++)
                {
                    if (UTDMScoreboardRow* NewRow = CreateWidget<UTDMScoreboardRow>(this, RowWidgetClass))
                    {
                        ScoreList->AddChildToVerticalBox(NewRow);
                        ScoreRows.Add(NewRow);
                    }
                }
            }

            for (int32 i = 0; i < ScoreRows.Num(); i++)
            {
                if (GS->TeamScores.IsValidIndex(i))
                {
                    ScoreRows[i]->UpdateRow(i, GS->TeamScores[i]);
                }
            }
        }
    }
}