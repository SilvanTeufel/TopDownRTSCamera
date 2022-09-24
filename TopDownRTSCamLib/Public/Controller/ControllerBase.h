// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hud/HUDBase.h"
#include "Characters/CameraBase.h"
#include "Characters/CharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "ControllerBase.generated.h"


UCLASS()
class TOPDOWNRTSCAMLIB_API AControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AControllerBase();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	AHUDBase* HUDPtr;
	ACameraBase* CameraPtr;

protected:

	void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShiftPressed", Keywords = "TopDownRTSCamLib ShiftPressed"), Category = TopDownRTSCamLib)
		void ShiftPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShiftReleased", Keywords = "TopDownRTSCamLib ShiftReleased"), Category = TopDownRTSCamLib)
		void ShiftReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LeftClickPressed", Keywords = "TopDownRTSCamLib LeftClickPressed"), Category = TopDownRTSCamLib)
		void LeftClickPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LeftClickReleased", Keywords = "TopDownRTSCamLib LeftClickReleased"), Category = TopDownRTSCamLib)
		void LeftClickReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RightClickPressed", Keywords = "TopDownRTSCamLib RightClickPressed"), Category = TopDownRTSCamLib)
		void RightClickPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SpacePressed", Keywords = "TopDownRTSCamLib SpacePressed"), Category = TopDownRTSCamLib)
		void SpacePressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SpaceReleased", Keywords = "TopDownRTSCamLib SpaceReleased"), Category = TopDownRTSCamLib)
		void SpaceReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "QPressed", Keywords = "TopDownRTSCamLib QPressed"), Category = TopDownRTSCamLib)
		void QPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WPressed", Keywords = "TopDownRTSCamLib WPressed"), Category = TopDownRTSCamLib)
		void WPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "APressed", Keywords = "TopDownRTSCamLib APressed"), Category = TopDownRTSCamLib)
		void APressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AReleased", Keywords = "TopDownRTSCamLib AReleased"), Category = TopDownRTSCamLib)
		void AReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JumpCamera", Keywords = "TopDownRTSCamLib JumpCamera"), Category = TopDownRTSCamLib)
		void JumpCamera();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StrgPressed", Keywords = "TopDownRTSCamLib StrgPressed"), Category = TopDownRTSCamLib)
		void StrgPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "StrgReleased", Keywords = "TopDownRTSCamLib StrgReleased"), Category = TopDownRTSCamLib)
		void StrgReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomIn", Keywords = "TopDownRTSCamLib ZoomIn"), Category = TopDownRTSCamLib)
		void ZoomIn();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomOut", Keywords = "TopDownRTSCamLib ZoomOut"), Category = TopDownRTSCamLib)
		void ZoomOut();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomStop", Keywords = "TopDownRTSCamLib ZoomStop"), Category = TopDownRTSCamLib)
		void ZoomStop();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CamLeft", Keywords = "TopDownRTSCamLib CamLeft"), Category = TopDownRTSCamLib)
		void CamLeft();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CamRight", Keywords = "TopDownRTSCamLib CamRight"), Category = TopDownRTSCamLib)
		void CamRight();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ControllDirectionToMouse", Keywords = "TopDownRTSCamLib ControllDirectionToMouse"), Category = TopDownRTSCamLib)
		void ControllDirectionToMouse(ACharacterBase* SelectedActor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ToggleLockCameraToCharacter", Keywords = "TopDownRTSCamLib ToggleLockCameraToCharacter"), Category = TopDownRTSCamLib)
		void ToggleLockCameraToCharacter();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TabPressed", Keywords = "TopDownRTSCamLib TabPressed"), Category = TopDownRTSCamLib)
		void TabPressed();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TabReleased", Keywords = "TopDownRTSCamLib TabReleased"), Category = TopDownRTSCamLib)
		void TabReleased();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnForward", Keywords = "TopDownRTSCamLib CameraPawnForward"), Category = TopDownRTSCamLib)
		void CameraPawnForward();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnBackward", Keywords = "TopDownRTSCamLib CameraPawnBackward"), Category = TopDownRTSCamLib)
		void CameraPawnBackward();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnLeft", Keywords = "TopDownRTSCamLib CameraPawnLeft"), Category = TopDownRTSCamLib)
		void CameraPawnLeft();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnRight", Keywords = "TopDownRTSCamLib CameraPawnRight"), Category = TopDownRTSCamLib)
		void CameraPawnRight();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnForwardR", Keywords = "TopDownRTSCamLib CameraPawnForwardR"), Category = TopDownRTSCamLib)
		void CameraPawnForwardR();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnBackwardR", Keywords = "TopDownRTSCamLib CameraPawnBackwardR"), Category = TopDownRTSCamLib)
		void CameraPawnBackwardR();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnLeftR", Keywords = "TopDownRTSCamLib CameraPawnLeftR"), Category = TopDownRTSCamLib)
		void CameraPawnLeftR();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CameraPawnRightR", Keywords = "TopDownRTSCamLib CameraPawnRightR"), Category = TopDownRTSCamLib)
		void CameraPawnRightR();

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "IsShiftPressed", Keywords = "TopDownRTSCamLib IsShiftPressed"), Category = TopDownRTSCamLib)
		bool IsShiftPressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "AIsPressed", Keywords = "TopDownRTSCamLib AIsPressed"), Category = TopDownRTSCamLib)
		bool AIsPressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "IsStrgPressed", Keywords = "TopDownRTSCamLib IsStrgPressed"), Category = TopDownRTSCamLib)
		bool IsStrgPressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "IsSpacePressed", Keywords = "TopDownRTSCamLib IsSpacePressed"), Category = TopDownRTSCamLib)
		bool IsSpacePressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "LockCameraToCharacter", Keywords = "TopDownRTSCamLib LockCameraToCharacter"), Category = TopDownRTSCamLib)
		bool LockCameraToCharacter = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "SelectedActors", Keywords = "TopDownRTSCamLib SelectedActors"), Category = TopDownRTSCamLib)
		TArray <ACharacterBase*> SelectedActors;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "MovingActors", Keywords = "TopDownRTSCamLib MovingActors"), Category = TopDownRTSCamLib)
		TArray <ACharacterBase*> MovingActors;
};
