// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.


#include "Animations/CharacterBaseAnimInstance.h"
#include "Characters/CharacterBase.h"


UCharacterBaseAnimInstance::UCharacterBaseAnimInstance()
{
	CharAnimState = CharacterData::Idle;
}

void UCharacterBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UCharacterBaseAnimInstance::NativeUpdateAnimation(float Deltaseconds)
{
	Super::NativeUpdateAnimation(Deltaseconds);
	AActor* OwningActor = GetOwningActor();

	if (OwningActor != nullptr) {

		ACharacterBase* Actor = Cast<ACharacterBase>(OwningActor);
		if (Actor != nullptr) {
			CharAnimState = Actor->GetAnimState();
		}
	}
}
