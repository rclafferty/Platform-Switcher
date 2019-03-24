// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"

void UGameWidget::Load()
{
	const FName TextBlockName = FName(TEXT("MessageBlock"));

	if (MessageText == nullptr)
	{
		MessageText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameWidget::OnGameOver(bool win)
{
	/* if (MessageText != nullptr)
	{
		if (win)
		{
			MessageText->SetText(FText::FromString(FString(TEXT("You won!\nPress R to play again."))));
		}
	}*/

	FText endMessage;

	if (win)
	{
		FText winMessage = FText::FromString(FString(TEXT("You won!\nPress R to play again.")));

		endMessage = winMessage;
	}
	else
	{
		FText loseMessage = FText::FromString(FString(TEXT("Uh oh! You hit an obstacle!\nPress R to try again.")));

		endMessage = loseMessage;
	}

	SetMessageText(endMessage);
}

void UGameWidget::SetMessageText(FText text)
{
	if (MessageText != nullptr)
	{
		MessageText->SetText(text);
	}
}