// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "CameraBase.generated.h"


UCLASS()
class TOPDOWNRTSCAMLIB_API ACameraBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACameraBase(const FObjectInitializer& ObjectInitializer);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateCameraComp", Keywords = "TopDownRTSCamLib CreateCameraComp"), Category = TopDownRTSCamLib)
		void CreateCameraComp();

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "RootScene", Keywords = "TopDownRTSCamLib RootScene"), Category = TopDownRTSCamLib)
		USceneComponent* RootScene;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "SpringArm", Keywords = "TopDownRTSCamLib SpringArm"), Category = TopDownRTSCamLib)
		USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "SpringArmRotator", Keywords = "TopDownRTSCamLib SpringArmRotator"), Category = TopDownRTSCamLib)
		FRotator SpringArmRotator = FRotator(-50, 0, 0);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "CameraComp", Keywords = "TopDownRTSCamLib CameraComp"), Category = TopDownRTSCamLib)
		UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "PC", Keywords = "TopDownRTSCamLib PC"), Category = TopDownRTSCamLib)
		APlayerController* PC;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetViewPortScreenSizes", Keywords = "TopDownRTSCamLib GetViewPortScreenSizes"), Category = TopDownRTSCamLib)
		void GetViewPortScreenSizes(int x);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SpawnControllWidget", Keywords = "TopDownRTSCamLib SpawnControllWidget"), Category = TopDownRTSCamLib)
		void SpawnControllWidget();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetCameraPanDirection", Keywords = "TopDownRTSCamLib GetCameraPanDirection"), Category = TopDownRTSCamLib)
		FVector GetCameraPanDirection();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PanMoveCamera", Keywords = "TopDownRTSCamLib PanMoveCamera"), Category = TopDownRTSCamLib)
		void PanMoveCamera(const FVector& PanDirection);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Margin", Keywords = "TopDownRTSCamLib Margin"), Category = TopDownRTSCamLib)
		float Margin = 15;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ScreenSizeX", Keywords = "TopDownRTSCamLib ScreenSizeX"), Category = TopDownRTSCamLib)
		int32 ScreenSizeX;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ScreenSizeY", Keywords = "TopDownRTSCamLib ScreenSizeY"), Category = TopDownRTSCamLib)
		int32 ScreenSizeY;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "GetViewPortScreenSizesState", Keywords = "TopDownRTSCamLib GetViewPortScreenSizesState"), Category = TopDownRTSCamLib)
		int GetViewPortScreenSizesState = 1; // Set 2 for System Resolution

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "CamSpeed", Keywords = "TopDownRTSCamLib CamSpeed"), Category = TopDownRTSCamLib)
		float CamSpeed = 80;

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

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CamStop", Keywords = "TopDownRTSCamLib CamStop"), Category = TopDownRTSCamLib)
		void CamStop();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CamRotationTick", Keywords = "TopDownRTSCamLib CamRotationTick"), Category = TopDownRTSCamLib)
		void CamRotationTick();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JumpCamera", Keywords = "TopDownRTSCamLib JumpCamera"), Category = TopDownRTSCamLib)
		void JumpCamera(FHitResult Hit);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMousePos2D", Keywords = "TopDownRTSCamLib GetMousePos2D"), Category = TopDownRTSCamLib)
		FVector2D GetMousePos2D();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Zoom", Keywords = "TopDownRTSCamLib Zoom"), Category = TopDownRTSCamLib)
		void Zoom();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomOutToPosition", Keywords = "TopDownRTSCamLib ZoomOutToPosition"), Category = TopDownRTSCamLib)
		void ZoomOutToPosition();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CamMoveAndZoomTick", Keywords = "TopDownRTSCamLib CamMoveAndZoomTick"), Category = TopDownRTSCamLib)
		void CamMoveAndZoomTick();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomInToPosition", Keywords = "TopDownRTSCamLib ZoomInToPosition"), Category = TopDownRTSCamLib)
		void ZoomInToPosition();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LockOnCharacter", Keywords = "TopDownRTSCamLib LockOnCharacter"), Category = TopDownRTSCamLib)
		void LockOnCharacter(ACharacter* SelectedActor);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ZoomOutPosition", Keywords = "TopDownRTSCamLib ZoomOutPosition"), Category = TopDownRTSCamLib)
		float ZoomOutPosition = 20000.f;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ZoomPosition", Keywords = "TopDownRTSCamLib ZoomPosition"), Category = TopDownRTSCamLib)
		float ZoomPosition = 1500.f;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "PitchValue", Keywords = "TopDownRTSCamLib PitchValue"), Category = TopDownRTSCamLib)
		float PitchValue = 0.f;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "YawValue", Keywords = "TopDownRTSCamLib YawValue"), Category = TopDownRTSCamLib)
		float YawValue = 0.f;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "RollValue", Keywords = "TopDownRTSCamLib RollValue"), Category = TopDownRTSCamLib)
		float RollValue = 0.f;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "RollCamRight", Keywords = "TopDownRTSCamLib RollCamRight"), Category = TopDownRTSCamLib)
		bool RollCamRight = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "RollCamLeft", Keywords = "TopDownRTSCamLib RollCamLeft"), Category = TopDownRTSCamLib)
		bool RollCamLeft = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ZoomCamOut", Keywords = "TopDownRTSCamLib ZoomCamOut"), Category = TopDownRTSCamLib)
		bool ZoomCamOut = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ZoomCamIn", Keywords = "TopDownRTSCamLib ZoomCamIn"), Category = TopDownRTSCamLib)
		bool ZoomCamIn = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ZoomCamOutToPosition", Keywords = "TopDownRTSCamLib ZoomCamOutToPosition"), Category = TopDownRTSCamLib)
		bool ZoomCamOutToPosition = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "MoveCamForward", Keywords = "TopDownRTSCamLib MoveCamForward"), Category = TopDownRTSCamLib)
		bool MoveCamForward = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "MoveCamBackward", Keywords = "TopDownRTSCamLib MoveCamBackward"), Category = TopDownRTSCamLib)
		bool MoveCamBackward = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "MoveCamLeft", Keywords = "TopDownRTSCamLib MoveCamLeft"), Category = TopDownRTSCamLib)
		bool MoveCamLeft = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "MoveCamRight", Keywords = "TopDownRTSCamLib MoveCamRight"), Category = TopDownRTSCamLib)
		bool MoveCamRight = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "startTime", Keywords = "TopDownRTSCamLib startTime"), Category = TopDownRTSCamLib)
		float startTime = 0.f;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "CamAngle", Keywords = "TopDownRTSCamLib CamAngle"), Category = TopDownRTSCamLib)
		int CamAngle = 0;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "DisableTick", Keywords = "TopDownRTSCamLib DisableTick"), Category = TopDownRTSCamLib)
		bool DisableTick = false;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "DisableBeginPlay", Keywords = "TopDownRTSCamLib DisableBeginPlay"), Category = TopDownRTSCamLib)
		bool DisableBeginPlay = false;


	// Action Interface
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "ControlWidgetComp", Keywords = "TopDownRTSCamLib ControlWidgetComp"), Category = TopDownRTSCamLib)
		class UWidgetComponent* ControlWidgetComp;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ControlWidgetRotator", Keywords = "TopDownRTSCamLib ControlWidgetRotator"), Category = TopDownRTSCamLib)
		FRotator ControlWidgetRotation = FRotator(50, 180, 0);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ControlWidgetLocation", Keywords = "TopDownRTSCamLib ControlWidgetLocation"), Category = TopDownRTSCamLib)
		FVector ControlWidgetLocation = FVector(400.f, -350.0f, -250.0f);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "ControlWidgetHideLocation", Keywords = "TopDownRTSCamLib ControlWidgetHideLocation"), Category = TopDownRTSCamLib)
		FVector ControlWidgetHideLocation = FVector(400.f, -2500.0f, -250.0f);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HideControlWidget", Keywords = "TopDownRTSCamLib HideControlWidget"), Category = TopDownRTSCamLib)
		void HideControlWidget();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowControlWidget", Keywords = "TopDownRTSCamLib ShowControlWidget"), Category = TopDownRTSCamLib)
		void ShowControlWidget();

};
