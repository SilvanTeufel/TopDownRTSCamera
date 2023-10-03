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
//#include "HeadMountedDisplayFunctionLibrary.h"
#include "Controller/Input/InputConfig.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Characters/CharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Core/DataTX.h"
#include "InputMappingContext.h"
#include "CameraBase.generated.h"


UCLASS()
class TOPDOWNRTSCAMLIB_API ACameraBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACameraBase(const FObjectInitializer& ObjectInitializer);

	UCapsuleComponent* GetCameraBaseCapsule() const {
		return GetCapsuleComponent();
	}
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = RTSUnitTemplate)
		void SetActorBasicLocation();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreateCameraComp", Keywords = "TopDownRTSTemplate CreateCameraComp"), Category = TopDownRTSTemplate)
		void CreateCameraComp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "RootScene", Keywords = "TopDownRTSTemplate RootScene"), Category = TopDownRTSTemplate)
		USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SpringArm", Keywords = "TopDownRTSTemplate SpringArm"), Category = TopDownRTSTemplate)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SpringArmRotator", Keywords = "TopDownRTSTemplate SpringArmRotator"), Category = TopDownRTSTemplate)
		FRotator SpringArmRotator = FRotator(-50, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CameraComp", Keywords = "TopDownRTSTemplate CameraComp"), Category = TopDownRTSTemplate)
		UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "PC", Keywords = "TopDownRTSTemplate PC"), Category = TopDownRTSTemplate)
		APlayerController* PC;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Inverter", Keywords = "TopDownRTSTemplate Inverter"), Category = TopDownRTSCamLib)
		float Inverter = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CameraDistanceToCharacter", Keywords = "TopDownRTSTemplate CameraDistanceToCharacter"), Category = TopDownRTSCamLib)
		float CameraDistanceToCharacter;

	UFUNCTION( BlueprintCallable, meta = (DisplayName = "PanMoveCamera", Keywords = "TopDownRTSTemplate PanMoveCamera"), Category = TopDownRTSTemplate)
		void PanMoveCamera(const FVector& NewPanDirection);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Margin", Keywords = "TopDownRTSTemplate Margin"), Category = TopDownRTSTemplate)
		float Margin = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ScreenSizeX", Keywords = "TopDownRTSTemplate ScreenSizeX"), Category = TopDownRTSTemplate)
		int32 ScreenSizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ScreenSizeY", Keywords = "TopDownRTSTemplate ScreenSizeY"), Category = TopDownRTSTemplate)
		int32 ScreenSizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "GetViewPortScreenSizesState", Keywords = "TopDownRTSTemplate GetViewPortScreenSizesState"), Category = TopDownRTSTemplate)
		int GetViewPortScreenSizesState = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		FVector CurrentCamSpeed = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float CamActorRespawnZLocation = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float ForceRespawnZLocation = -200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float AccelerationRate = 7500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float DecelerationRate = 15000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CamSpeed", Keywords = "TopDownRTSTemplate CamSpeed"), Category = TopDownRTSTemplate)
		float CamSpeed = 7000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = RTSUnitTemplate)
		float ZoomSpeed = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = RTSUnitTemplate)
		float FastZoomSpeed = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float ZoomAccelerationRate = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float ZoomDecelerationRate = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "EdgeScrollCamSpeed", Keywords = "RTSUnitTemplate EdgeScrollCamSpeed"), Category = RTSUnitTemplate)
		float EdgeScrollCamSpeed = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float SpringArmMinRotator = -10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float SpringArmMaxRotator = -50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float SpringArmStartRotator = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float SpringArmRotatorSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float SpringArmRotatorMaxSpeed = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
		float SpringArmRotatorAcceleration = 0.05f;

	UFUNCTION(BlueprintCallable, Category = RTSUnitTemplate)
		void RotateSpringArm(bool Invert = false);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomIn", Keywords = "RTSUnitTemplate ZoomIn"), Category = RTSUnitTemplate)
		void ZoomIn(float ZoomMultiplier, bool Decelerate = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomOut", Keywords = "RTSUnitTemplate ZoomOut"), Category = RTSUnitTemplate)
		void ZoomOut(float ZoomMultiplier, bool Decelerate = false);

	UFUNCTION(BlueprintCallable, Category = RTSUnitTemplate)
		void AdjustSpringArmRotation(float Difference, float& OutRotationValue);

	UFUNCTION(BlueprintCallable, Category = RTSUnitTemplate)
		bool RotateFree(FVector MouseLocation);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RotateCamLeft", Keywords = "RTSUnitTemplate RotateCamLeft"), Category = TopDownRTSCamLib)
		bool RotateCamLeft(float Add, bool stopCam = false); // CamRotationOffset
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RotateCamRight", Keywords = "RTSUnitTemplate RotateCamRight"), Category = TopDownRTSCamLib)
		bool RotateCamRight(float Add, bool stopCam = false); // CamRotationOffset
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RotateCamLeft", Keywords = "RTSUnitTemplate RotateCamLeft"), Category = TopDownRTSCamLib)
		bool RotateCamLeftTo(float Position, float Add);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RotateCamRight", Keywords = "RTSUnitTemplate RotateCamRight"), Category = TopDownRTSCamLib)
		bool RotateCamRightTo(float Position, float Add);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "JumpCamera", Keywords = "TopDownRTSTemplate JumpCamera"), Category = TopDownRTSTemplate)
		void JumpCamera(FHitResult Hit);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetMousePos2D", Keywords = "TopDownRTSTemplate GetMousePos2D"), Category = TopDownRTSTemplate)
		FVector2D GetMousePos2D();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Zoom", Keywords = "TopDownRTSTemplate Zoom"), Category = TopDownRTSTemplate)
		void Zoom();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomOutToPosition", Keywords = "TopDownRTSTemplate ZoomOutToPosition"), Category = TopDownRTSTemplate)
		bool ZoomOutToPosition(float Distance, const FVector SelectedActorPosition = FVector(0.f,0.f,0.f));
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomInToPosition", Keywords = "TopDownRTSTemplate ZoomInToPosition"), Category = TopDownRTSTemplate)
		bool ZoomInToPosition(float Distance, const FVector SelectedActorPosition = FVector(0.f,0.f,0.f));

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LockOnUnit", Keywords = "TopDownRTSTemplate LockOnUnit"), Category = TopDownRTSTemplate)
		void LockOnUnit(ACharacterBase* Unit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ZoomOutPosition", Keywords = "RTSUnitTemplate ZoomOutPosition"), Category = RTSUnitTemplate)
	float ZoomOutPosition = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ZoomPosition", Keywords = "RTSUnitTemplate ZoomPosition"), Category = RTSUnitTemplate)
	float ZoomPosition = 2000.f; // 1500.f

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "PitchValue", Keywords = "RTSUnitTemplate PitchValue"), Category = RTSUnitTemplate)
	float PitchValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "YawValue", Keywords = "RTSUnitTemplate YawValue"), Category = RTSUnitTemplate)
	float YawValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	float CurrentRotationValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	float RotationIncreaser = 0.01f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	float RollValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	bool AutoLockOnSelect = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	bool DisableEdgeScrolling = false;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomThirdPersonPosition", Keywords = "TopDownRTSCamLib ZoomThirdPersonPosition"), Category = TopDownRTSCamLib)
		bool IsCharacterDistanceTooLow(float Distance, const FVector SelectedActorPosition = FVector(0.f,0.f,0.f));

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "IsCharacterDistanceTooHigh", Keywords = "TopDownRTSCamLib IsCharacterDistanceTooHigh"), Category = RTSUnitTemplate)
		bool IsCharacterDistanceTooHigh(float Distance, const FVector SelectedActorPosition);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ZoomThirdPersonPosition", Keywords = "TopDownRTSCamLib ZoomThirdPersonPosition"), Category = TopDownRTSCamLib)
		bool ZoomInToThirdPerson(const FVector SelectedActorPosition = FVector(0.f,0.f,0.f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ZoomThirdPersonPosition", Keywords = "TopDownRTSCamLib ZoomThirdPersonPosition"), Category = TopDownRTSCamLib)
		float ZoomThirdPersonPosition = 600.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CamRotationOffset", Keywords = "TopDownRTSCamLib CamRotationOffset"), Category = TopDownRTSCamLib)
		float CamRotationOffset = 11.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "AddCamRotation", Keywords = "TopDownRTSCamLib AddCamRotation"), Category = RTSUnitTemplate)
		float AddCamRotation = 0.75f;
	
	UPROPERTY(EditAnywhere, meta = (DisplayName = "CameraAngles", Keywords = "TopDownRTSCamLib CameraAngles"), Category = TopDownRTSCamLib)
		float CameraAngles[4] = { 0.f, 90.f, 180.f, 270.f };

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "RotationDegreeStep", Keywords = "TopDownRTSCamLib RotationDegreeStep"), Category = TopDownRTSCamLib)
		float RotationDegreeStep = 90.f;
	
	bool IsCameraInAngle()
	{
		if(YawValue == 360.f) YawValue = 0.f;
		bool IsInAngle = false;
		for( int i = 0; i < 4 ; i++)
		{
			if(YawValue == CameraAngles[i]) IsInAngle = true;
		}
		return IsInAngle;
	}

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MoveCamToForward", Keywords = "TopDownRTSCamLib MoveCamToForward"), Category = RTSUnitTemplate)
		void MoveCamToForward(float DeltaTime, bool Decelerate = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MoveCamToBackward", Keywords = "TopDownRTSCamLib MoveCamToBackward"), Category = RTSUnitTemplate)
		void MoveCamToBackward(float DeltaTime, bool Decelerate = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MoveCamToLeft", Keywords = "TopDownRTSCamLib MoveCamToLeft"), Category = RTSUnitTemplate)
		void MoveCamToLeft(float DeltaTime, bool Decelerate = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MoveCamToRight", Keywords = "TopDownRTSCamLib MoveCamToRight"), Category = RTSUnitTemplate)
		void MoveCamToRight(float DeltaTime, bool Decelerate = false);
	
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "StartTime", Keywords = "TopDownRTSCamLib StartTime"), Category = TopDownRTSCamLib)
		float StartTime = 0.f;

	// Orbit
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "OrbitCamLeft", Keywords = "RTSUnitTemplate OrbitCamLeft"), Category = TopDownRTSCamLib)
	bool OrbitCamLeft(float Add);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	FVector OrbitLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	float OrbitRotationValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	float OrbitIncreaser = 0.0001f; //0.0001f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	float OrbitSpeed = 0.033f; //0.0010f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RTSUnitTemplate)
	float MovePositionCamSpeed = 1.0f;
	
	// Control Widget

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "ControlWidgetComp", Keywords = "TopDownRTSTemplate ControlWidgetComp"), Category = TopDownRTSTemplate)
		class UWidgetComponent* ControlWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ControlWidgetRotator", Keywords = "TopDownRTSTemplate ControlWidgetRotator"), Category = TopDownRTSTemplate)
		FRotator ControlWidgetRotation = FRotator(50, 180, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ControlWidgetLocation", Keywords = "TopDownRTSTemplate ControlWidgetLocation"), Category = TopDownRTSTemplate)
		FVector2D ControlWidgetLocation = FVector2D(0.5f, 0.5f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ControlWidgetHideLocation", Keywords = "TopDownRTSTemplate ControlWidgetHideLocation"), Category = TopDownRTSTemplate)
		FVector ControlWidgetHideLocation = FVector(400.f, -4500.0f, -250.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TopDownRTSTemplate)
		bool ShowControlWidgetAtStart = true;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "HideControlWidget", Keywords = "TopDownRTSTemplate HideControlWidget"), Category = TopDownRTSTemplate)
		void HideControlWidget();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ShowControlWidget", Keywords = "TopDownRTSTemplate ShowControlWidget"), Category = TopDownRTSTemplate)
		void ShowControlWidget();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SpawnControlWidget", Keywords = "TopDownRTSTemplate SpawnControlWidget"), Category = TopDownRTSTemplate)
		void SetControlWidgetLocation();

	
/////// Loading Widget //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TopDownRTSTemplate)
		class UWidgetComponent* LoadingWidgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TopDownRTSTemplate)
		FRotator LoadingWidgetRotation = FRotator(50.f, 180, 0.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TopDownRTSTemplate)
		FVector LoadingWidgetLocation = FVector(150.f, 000.0f, -150.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = TopDownRTSTemplate)
		FVector LoadingWidgetHideLocation = FVector(300.f, -2200.0f, -250.0f);

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void DeSpawnLoadingWidget();

	UFUNCTION(BlueprintCallable, Category = TopDownRTSTemplate)
		void SpawnLoadingWidget();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	UPROPERTY(EditAnywhere, Category = TopDownRTSTemplate)
	FVector WidgetOffset = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TopDownRTSTemplate)
	float WidgetDistance = 0.05f;



	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CameraState", Keywords = "TopDownRTSTemplate CameraState"), Category = TopDownRTSTemplate)
		TEnumAsByte<CameraData::CameraState> CameraState = CameraData::UseScreenEdges;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetCameraState", Keywords = "TopDownRTSCamLib SetCameraState"), Category = TopDownRTSTemplate)
		void SetCameraState(TEnumAsByte<CameraData::CameraState> NewCameraState);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetCameraState", Keywords = "TopDownRTSCamLib GetCameraState"), Category = TopDownRTSTemplate)
		TEnumAsByte<CameraData::CameraState> GetCameraState();

	
};
