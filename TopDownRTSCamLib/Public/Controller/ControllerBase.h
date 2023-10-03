// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hud/HUDBase.h"
#include "Characters//ExtendedCameraBase.h"
#include "GameFramework/PlayerController.h"
#include "ControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRTSCAMLIB_API AControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AControllerBase();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	AHUDBase* HUDBase;
	AExtendedCameraBase* ExtendedCameraBase;
	
public:

	void Tick(float DeltaSeconds);


	
	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void LockCamTick();
	
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShiftPressed", Keywords = "TopDownRTSTemplate ShiftPressed"), Category = TopDownRTSTemplate)
		void ShiftPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShiftReleased", Keywords = "TopDownRTSTemplate ShiftReleased"), Category = TopDownRTSTemplate)
		void ShiftReleased();

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void LeftClickPressed();

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void LeftClickReleased();

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void SelectUnit(int Index);

	
	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void RightClickPressed();

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void RightClickReleased();

	UPROPERTY(BlueprintReadWrite, Category = TopDownRTSTemplate)
		bool IsRightClickPressed = false;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "APressed", Keywords = "TopDownRTSTemplate APressed"), Category = TopDownRTSTemplate)
		void APressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AReleased", Keywords = "TopDownRTSTemplate AReleased"), Category = TopDownRTSTemplate)
		void AReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AReleased", Keywords = "TopDownRTSTemplate AReleased"), Category = TopDownRTSTemplate)
		void SReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RPressed", Keywords = "TopDownRTSTemplate RPressed"), Category = TopDownRTSTemplate)
		void RPressed();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "FPressed", Keywords = "TopDownRTSTemplate FPressed"), Category = TopDownRTSTemplate)
		void FPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CPressed", Keywords = "TopDownRTSTemplate CPressed"), Category = TopDownRTSTemplate)
		void CPressed();

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void DPressed();

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void DReleased();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "EPressed", Keywords = "TopDownRTSTemplate EPressed"), Category = TopDownRTSTemplate)
		void EPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XPressed", Keywords = "TopDownRTSTemplate XPressed"), Category = TopDownRTSTemplate)
		void XPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WPressed", Keywords = "TopDownRTSTemplate WPressed"), Category = TopDownRTSTemplate)
		void WPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WPressed", Keywords = "TopDownRTSTemplate WPressed"), Category = TopDownRTSTemplate)
		void WReleased();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "YPressed", Keywords = "TopDownRTSTemplate YPressed"), Category = TopDownRTSTemplate)
		void YPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TPressed", Keywords = "TopDownRTSTemplate TPressed"), Category = TopDownRTSTemplate)
		void TPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "QPressed", Keywords = "TopDownRTSTemplate QPressed"), Category = TopDownRTSTemplate)
		void QPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "QReleased", Keywords = "TopDownRTSTemplate QReleased"), Category = TopDownRTSTemplate)
		void QReleased();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JumpCamera", Keywords = "TopDownRTSTemplate JumpCamera"), Category = TopDownRTSTemplate)
		void JumpCamera();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StrgPressed", Keywords = "TopDownRTSTemplate StrgPressed"), Category = TopDownRTSTemplate)
		void StrgPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StrgReleased", Keywords = "TopDownRTSTemplate StrgReleased"), Category = TopDownRTSTemplate)
		void StrgReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomIn", Keywords = "TopDownRTSTemplate ZoomIn"), Category = TopDownRTSTemplate)
		void ZoomIn();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomOut", Keywords = "TopDownRTSTemplate ZoomOut"), Category = TopDownRTSTemplate)
		void ZoomOut();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AltPressed", Keywords = "TopDownRTSTemplate AltPressed"), Category = TopDownRTSTemplate)
		void AltPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AltReleased", Keywords = "TopDownRTSTemplate AltReleased"), Category = TopDownRTSTemplate)
		void AltReleased();

public:
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "IsShiftPressed", Keywords = "TopDownRTSTemplate IsShiftPressed"), Category = TopDownRTSTemplate)
		bool IsShiftPressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "AttackToggled", Keywords = "TopDownRTSTemplate AttackToggled"), Category = TopDownRTSTemplate)
		bool AttackToggled = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "AttackToggled", Keywords = "TopDownRTSTemplate AttackToggled"), Category = TopDownRTSTemplate)
		bool GravityToggled = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "IsStrgPressed", Keywords = "TopDownRTSTemplate IsStrgPressed"), Category = TopDownRTSTemplate)
		bool IsStrgPressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "IsSpacePressed", Keywords = "TopDownRTSTemplate IsSpacePressed"), Category = TopDownRTSTemplate)
		bool IsSpacePressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "AltIsPressed", Keywords = "TopDownRTSTemplate AltIsPressed"), Category = TopDownRTSTemplate)
		bool AltIsPressed = false;
	
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "LeftClickisPressed", Keywords = "TopDownRTSTemplate LeftClickisPressed"), Category = TopDownRTSTemplate)
		bool LeftClickIsPressed = false;
	
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "LockCameraToUnit", Keywords = "TopDownRTSTemplate LockCameraToUnit"), Category = TopDownRTSTemplate)
		bool LockCameraToUnit = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "AIsPressed", Keywords = "TopDownRTSCamLib AIsPressed"), Category = RTSUnitTemplate)
		int AIsPressedState = 0;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "DIsPressed", Keywords = "TopDownRTSCamLib DIsPressed"), Category = RTSUnitTemplate)
		int DIsPressedState = 0;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "WIsPressed", Keywords = "TopDownRTSCamLib WIsPressed"), Category = RTSUnitTemplate)
		int WIsPressedState = 0;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "SIsPressed", Keywords = "TopDownRTSCamLib SIsPressed"), Category = RTSUnitTemplate)
		int SIsPressedState = 0;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "QIsPressed", Keywords = "TopDownRTSCamLib QIsPressed"), Category = TopDownRTSCamLib)
		bool QIsPressed = false;

	UPROPERTY(BlueprintReadWrite,  Category = TopDownRTSCamLib)
		bool DIsPressed = false;
	
	UPROPERTY(BlueprintReadWrite, Category = RTSUnitTemplate)
		bool MiddleMouseIsPressed = false;
	
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "SelectedUnits", Keywords = "TopDownRTSTemplate SelectedUnits"), Category = TopDownRTSTemplate)
		TArray <ACharacterBase*> SelectedUnits;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "SelectedUnits", Keywords = "TopDownRTSTemplate SelectedUnits"), Category = TopDownRTSTemplate)
		int SelectedUnitCount = 0;
	
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "BotIsToggled", Keywords = "TopDownRTSTemplate BotIsToggled"), Category = TopDownRTSTemplate)
		bool BotIsToggled = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "LaserToggled", Keywords = "TopDownRTSTemplate LaserToggled"), Category = TopDownRTSTemplate)
		bool LaserToggled = false;

	UPROPERTY(BlueprintReadWrite, Category = TopDownRTSTemplate)
		int SelectedUnitId = 0;
};
