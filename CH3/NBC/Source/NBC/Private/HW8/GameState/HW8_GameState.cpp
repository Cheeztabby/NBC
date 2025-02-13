#include "HW8/GameState/HW8_GameState.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HW8/Actor/CoinItem.h"
#include "HW8/Actor/SpawnVolume.h"
#include "HW8/Character/HW8_Character.h"
#include "HW8/GameInstance/HW8_GameInstance.h"
#include "HW8/PlayerController/HW8_PlayerController.h"
#include "Kismet/GameplayStatics.h"

AHW8_GameState::AHW8_GameState()
{
}

void AHW8_GameState::BeginPlay()
{
	Super::BeginPlay();
	//StartLevel(); // 기존 프로젝트
	GetWorldTimerManager().SetTimer(HUDUpdateTimerHandle, this, &ThisClass::UpdateHUD, 0.1f, true);
	StartWave(); // 과제
}

void AHW8_GameState::StartWave()
{
	// Delete Prev Wave Items
	TArray<AActor*> WorldItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemBase::StaticClass(), WorldItems);
	for (AActor* WorldItem : WorldItems)
	{
		if (AItemBase* Item = Cast<AItemBase>(WorldItem))
		{
			Item->DestroyItem();
		}
	}
	
	if (AHW8_PlayerController* PlayerController = GetWorld()->GetFirstPlayerController<AHW8_PlayerController>())
	{
		PlayerController->ShowGameHUD();
	}
	if (const UHW8_GameInstance* GameInstance = Cast<UHW8_GameInstance>(GetGameInstance()))
	{
		CurrentLevelIndex = GameInstance->CurrentLevelIndex;
	}
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	if (FoundVolumes.Num() > 0)
	{
		if (const ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
		{
			for (int32 i = 0; i < ItemToSpawns[CurrentLevelIndex]; i++)
			{
				if (const AActor* SpawnedActor = SpawnVolume->SpawnRandomItem())
				{
					if (SpawnedActor->IsA(ACoinItem::StaticClass()))
					{
						SpawnedCoinCount++;
					}
				}
			}
		}
	}
	// 각 레벨별 사용하던 CurrentLevelIndex를 활용한 배열들을 한 웨이브에서 쓰도록 재활용
	GetWorldTimerManager().SetTimer(LevelTimerHandle, this, &ThisClass::UpdateWave, LevelDurations[CurrentLevelIndex],false);
}

void AHW8_GameState::UpdateWave()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	// Update Prev Player Score, LevelIndex(using WaveIndex)
	if (UHW8_GameInstance* GameInstance = Cast<UHW8_GameInstance>(GetGameInstance()))
	{
		AddScore(Score);
		CurrentLevelIndex++;
		GameInstance->CurrentLevelIndex = CurrentLevelIndex;
	}
	if (CurrentLevelIndex > MaxLevels)
	{
		OnGameOver();
	}
	else
	{
		StartWave();
	}
}


void AHW8_GameState::StartLevel()
{
	if (AHW8_PlayerController* PlayerController = GetWorld()->GetFirstPlayerController<AHW8_PlayerController>())
	{
		PlayerController->ShowGameHUD();
	}

	if (const UHW8_GameInstance* GameInstance = Cast<UHW8_GameInstance>(GetGameInstance()))
	{
		CurrentLevelIndex = GameInstance->CurrentLevelIndex;
	}

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	if (FoundVolumes.Num() > 0)
	{
		if (const ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
		{
			for (int32 i = 0; i < ItemToSpawns[CurrentLevelIndex]; i++)
			{
				if (const AActor* SpawnedActor = SpawnVolume->SpawnRandomItem())
				{
					if (SpawnedActor->IsA(ACoinItem::StaticClass()))
					{
						SpawnedCoinCount++;
					}
				}
			}
		}
	}
	GetWorldTimerManager().SetTimer(LevelTimerHandle, this, &ThisClass::OnLevelTimeUp,LevelDurations[CurrentLevelIndex], false);
}

int32 AHW8_GameState::GetScore() const
{
	return Score;
}

void AHW8_GameState::AddScore(const int32 Amount)
{
	if (UHW8_GameInstance* GameInstance = Cast<UHW8_GameInstance>(GetWorld()->GetGameInstance()))
	{
		GameInstance->AddToScore(Amount);
	}
}

void AHW8_GameState::OnLevelTimeUp()
{
	EndLevel();
}

void AHW8_GameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (UHW8_GameInstance* GameInstance = Cast<UHW8_GameInstance>(GetGameInstance()))
	{
		AddScore(Score);
		CurrentLevelIndex++;
		GameInstance->CurrentLevelIndex = CurrentLevelIndex;
	}

	if (CurrentLevelIndex > MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void AHW8_GameState::UpdateHUD() const
{
	if (const AHW8_PlayerController* PlayerController = GetWorld()->GetFirstPlayerController<AHW8_PlayerController>())
	{
		if (const UUserWidget* HUDWidget = PlayerController->GetHUDWidget())
		{
			if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
			{
				const float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
				TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
			}

			if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
			{
				if (const UHW8_GameInstance* GameInstance = Cast<UHW8_GameInstance>(GetGameInstance()))
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), GameInstance->TotalScore)));
				}
			}

			if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
			{
				if (bIsWaveVersion)
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d"), CurrentLevelIndex + 1)));
				}
				else
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
				}
			}

			if (UTextBlock* HpIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("HP"))))
			{
				if (AHW8_Character* Character = Cast<AHW8_Character>(GetWorld()->GetFirstPlayerController()->GetCharacter()))
				{
					HpIndexText->SetText(FText::FromString(FString::Printf(TEXT("Hp: %.1f"), Character->GetHealth())));
				}
			}
		}
	}
}

void AHW8_GameState::OnGameOver()
{
	if (AHW8_PlayerController* PlayerController = GetWorld()->GetFirstPlayerController<AHW8_PlayerController>())
	{
		PlayerController->ShowMainMenu(true);
	}
}

void AHW8_GameState::OnCoinCollected()
{
	CollectedCoinCount++;
	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndLevel();
	}
}
