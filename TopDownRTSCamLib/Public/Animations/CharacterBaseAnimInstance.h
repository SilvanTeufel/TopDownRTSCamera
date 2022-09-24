// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Core/DataTX.h"
#include "CharacterBaseAnimInstance.generated.h"


UCLASS()
class TOPDOWNRTSCAMLIB_API UCharacterBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCharacterBaseAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		FString AnimStateString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStatus)
		TEnumAsByte<CharacterStatus> CharAnimState;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float Deltaseconds) override;

};
