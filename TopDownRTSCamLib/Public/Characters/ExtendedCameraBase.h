// Copyright 2023 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CameraBase.h"
#include "ExtendedCameraBase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRTSCAMLIB_API AExtendedCameraBase : public ACameraBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputConfig* InputConfig;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MappingContext", Keywords = "TopDownRTSTemplate MappingContext"), Category = TopDownRTSCamLib)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MappingPriority", Keywords = "TopDownRTSTemplate MappingPriority"), Category = TopDownRTSCamLib)
	int32 MappingPriority;

	/** Handles Enhanced Keyboard Inputs */
	void Input_LeftClick_Pressed(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_LeftClick_Released(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_RightClick_Pressed(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_RightClick_Released(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_Ctrl_Pressed(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_Ctrl_Released(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_Tab_Pressed(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_Tab_Released(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_Shift_Pressed(const FInputActionValue& InputActionValue, int32 CamState);
	void Input_Shift_Released(const FInputActionValue& InputActionValue, int32 CamState);
	/** Handles Enhanced Keyboard Inputs */
	
	void SwitchControllerStateMachine(const FInputActionValue& InputActionValue, int32 NewCameraState);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TopDownRTSCamLib)
	bool BlockControls = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	



	
};
