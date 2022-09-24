// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Animations/CharacterBaseAnimInstance.h"
#include "Core/DataTX.h"
#include "CharacterBase.generated.h"


UCLASS()
class TOPDOWNRTSCAMLIB_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector MoveEndLocation;
	float Speed = 600.0f;
	float CalcAngle(FVector VectorOne, FVector VectorTwo);
	float CheckAngle(FVector VectorOne, float AngleOneX);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStatus)
		TEnumAsByte<CharacterStatus> CharAnimState;

	void setAnimState(TEnumAsByte<CharacterStatus> NewCharAnimState);
	TEnumAsByte<CharacterStatus> getAnimState();

	FVector ActualLocation;
	// RTSHud related ///////////
public:
	void SetSelected();
	void SetDeselected();
	/////////////////////////////
	UFUNCTION()
		void CreateIconNormalRadius();

	// RTSPlayerController related ///////////
public:
	TArray <FVector> MoveArray;
	int32 MoveArrayIterator;
	FVector ForwardVector;
	FVector LastDirection;
	float JumpHeight = 600.0f;
	int DoubleJumpCounter = 0;

	// SelectedCharacterIcon related /////////
protected:
	class ASelectedCharacterIcon* SelectedCharacterIcon;
	//////////////////////////////////////


private:
	// A decal that projects to the cursor location. //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
	////////////////////////////////////////

};
