#include "HW8/PlayerController/HW8_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HW8/GameInstance/HW8_GameInstance.h"
#include "HW8/GameState/HW8_GameState.h"
#include "Kismet/GameplayStatics.h"

AHW8_PlayerController::AHW8_PlayerController()
{
}

UUserWidget* AHW8_PlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void AHW8_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld()->GetMapName().Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}

void AHW8_PlayerController::ShowGameHUD()
{
	// 이미 화면이 띄워져 있는 경우
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}
		if(const UWorld* World = GetWorld())
		{
			if(const AHW8_GameState* GameState = World->GetGameState<AHW8_GameState>())
			{
				GameState->UpdateHUD();
			}
		}
	}
}

void AHW8_PlayerController::ShowMainMenu(const bool bIsRestart)
{
	// 이미 화면이 띄워져 있는 경우
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
		if(UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if(bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
	}
}

void AHW8_PlayerController::StartGame()
{
	if(UHW8_GameInstance* GameInstance = Cast<UHW8_GameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		GameInstance->CurrentLevelIndex = 0;
		GameInstance->TotalScore = 0;
	}
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BasicLevel"));
}
