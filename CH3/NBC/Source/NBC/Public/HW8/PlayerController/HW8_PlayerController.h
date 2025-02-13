#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HW8_PlayerController.generated.h"

UCLASS()
class NBC_API AHW8_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHW8_PlayerController();

	UFUNCTION(BlueprintPure, Category="HUD")
	UUserWidget* GetHUDWidget() const;

	UFUNCTION(BlueprintCallable, Category="HUD")
	void ShowGameHUD();

	UFUNCTION(BlueprintCallable, Category="Menu")
	void ShowMainMenu(const bool bIsRestart);

	UFUNCTION(BlueprintCallable, Category="Menu")
	void StartGame();
protected:
	virtual void BeginPlay() override;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HUD")
	TObjectPtr<UUserWidget> HUDWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Menu")
	TObjectPtr<UUserWidget> MainMenuWidgetInstance = nullptr;
};
