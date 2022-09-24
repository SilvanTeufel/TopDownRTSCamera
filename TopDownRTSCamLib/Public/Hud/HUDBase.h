// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "Characters/CharacterBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HUDBase.generated.h"


UCLASS()
class TOPDOWNRTSCAMLIB_API AHUDBase : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DrawHUD", Keywords = "TopDownRTSCamLib DrawHUD"), Category = TopDownRTSCamLib)
		virtual void DrawHUD(); // used in Tick();

	void Tick(float DeltaSeconds);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "InitialPoint", Keywords = "TopDownRTSCamLib InitialPoint"), Category = TopDownRTSCamLib)
		FVector2D InitialPoint; // Position of mouse on screen when pressed;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "CurrentPoint", Keywords = "TopDownRTSCamLib CurrentPoint"), Category = TopDownRTSCamLib)
		FVector2D CurrentPoint; // Position of mouse on screen while holding;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "RectangleScaleSelectionFactor", Keywords = "TopDownRTSCamLib RectangleScaleSelectionFactor"), Category = TopDownRTSCamLib)
		float RectangleScaleSelectionFactor = 0.9;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMousePos2D", Keywords = "TopDownRTSCamLib GetMousePos2D"), Category = TopDownRTSCamLib)
		FVector2D GetMousePos2D();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AimToMouse", Keywords = "TopDownRTSCamLib AimToMouse"), Category = TopDownRTSCamLib)
		void AimToMouse();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MoveActorsThroughWayPoints", Keywords = "TopDownRTSCamLib MoveActorsThroughWayPoints"), Category = TopDownRTSCamLib)
		void MoveActorsThroughWayPoints(TArray <ACharacterBase*> Actors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StartMovingActors", Keywords = "TopDownRTSCamLib StartMovingActors"), Category = TopDownRTSCamLib)
		void StartMovingActors(TArray <ACharacterBase*> Actors);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "setZeroActor", Keywords = "TopDownRTSCamLib setZeroActor"), Category = TopDownRTSCamLib)
		void setZeroActor(ACharacterBase* Actor);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "bStartSelecting", Keywords = "TopDownRTSCamLib bStartSelecting"), Category = TopDownRTSCamLib)
		bool bStartSelecting = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "FoundActors", Keywords = "TopDownRTSCamLib FoundActors"), Category = TopDownRTSCamLib)
		TArray <ACharacterBase*> FoundActors;
	
};
