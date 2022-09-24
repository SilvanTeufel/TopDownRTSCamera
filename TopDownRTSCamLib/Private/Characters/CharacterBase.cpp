// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.


#include "Characters/CharacterBase.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "UObject/ConstructorHelpers.h"

#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"

#include "Materials/Material.h" 
#include "Engine/World.h"
#include "Actors/SelectedCharacterIcon.h"


// Sets default values
ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/TopDownRTSCamLib/Materials/M_Ring_Aura.M_Ring_Aura'"));


	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	CursorToWorld->SetVisibility(false);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	if (RootComponent == nullptr) {
		RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	}


}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{

	Super::BeginPlay();


	FRotator NewRotation = FRotator(0, -90, 0);

	FQuat QuatRotation = FQuat(NewRotation);
	GetMesh()->SetRelativeRotation(QuatRotation, false, 0, ETeleportType::None);
}


// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				Params.AddIgnoredActor(this);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}


	switch (CharAnimState)
	{
	case Run:
	{
		ActualLocation = GetActorLocation();
		float vdist = FVector::Dist(ActualLocation, MoveEndLocation);
		if (vdist < 120.f) {
			CharAnimState = Idle;
		}
	}
	break;
	case Idle:
	{

	}
	break;
	}

}
////////////////////////////////////////////////////////////////////////////

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACharacterBase::CheckAngle(FVector Vector, float Angle) {

	float X = Vector.X;
	float Y = Vector.Y;

	if (Vector.X < 0.001 && Vector.X > -0.001 && Vector.Y > 0.000) {
		Angle = 90;
	}
	else if (Vector.X < 0.001 && Vector.X > -0.001 && Vector.Y < 0.000) {
		Angle = 270;
	}
	else if (Vector.Y < 0.001 && Vector.Y > -0.001 && Vector.X > 0.000) {
		Angle = 0.;
	}
	else if (Vector.Y < 0.001f && Vector.Y > -0.001 && Vector.X < 0.000) {
		Angle = 180;
	}
	else if (Vector.X > 0.000 && Vector.Y > 0.000) {
		Angle += 0.000;
	}
	else if (Vector.X < 0.000 && Vector.Y > 0.000) {
		Angle += 0.000;
	}
	else if (Vector.X > 0.000 && Vector.Y < 0.000) {
		Angle = 360 - Angle;
	}
	else if (Vector.X < 0.000 && Vector.Y < 0.000) {
		Angle = 360 - Angle;
	}
	else {
	}

	return Angle;
}

void ACharacterBase::setAnimState(TEnumAsByte<CharacterStatus> NewCharAnimState)
{
	CharAnimState = NewCharAnimState;
}

TEnumAsByte<CharacterStatus> ACharacterBase::getAnimState()
{
	return CharAnimState;
}

float ACharacterBase::CalcAngle(FVector VectorOne, FVector VectorTwo)
{
	float AngleOneX = acosf(UKismetMathLibrary::Vector_CosineAngle2D(VectorOne, FVector(1, 0, 0))) * (180 / 3.1415926);
	AngleOneX = CheckAngle(VectorOne, AngleOneX);

	float AngleTwoX = acosf(UKismetMathLibrary::Vector_CosineAngle2D(VectorTwo, FVector(1, 0, 0))) * (180 / 3.1415926);
	AngleTwoX = CheckAngle(VectorTwo, AngleTwoX);

	float AngleDiff = AngleOneX - AngleTwoX;
	return AngleOneX - AngleTwoX;
}


// RTSHud related //////////////////////////////////////////////////
void ACharacterBase::SetSelected()
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform SpellTransform;
	SpellTransform.SetLocation(FVector(500, 0, 0));
	SpellTransform.SetRotation(FQuat(FRotator::ZeroRotator));
	SelectedCharacterIcon = GetWorld()->SpawnActor<ASelectedCharacterIcon>(ASelectedCharacterIcon::StaticClass(), SpellTransform, SpawnParams);
	if (SelectedCharacterIcon) {
		SelectedCharacterIcon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Selection_Icon_Socket"));
		SelectedCharacterIcon->SetActorScale3D(FVector(1.0f, 1.0f, 0.05f));
	}
}

void ACharacterBase::SetDeselected()
{
	SelectedCharacterIcon->Destroy(true, false);
}
/////////////////////////////////////////////////////////////////////

void ACharacterBase::CreateIconNormalRadius()
{
	if (SelectedCharacterIcon) {
		FVector IconScale = SelectedCharacterIcon->GetActorScale3D();
		if (IconScale.X + 0.5 < 1.0f) {
			SelectedCharacterIcon->SetActorScale3D(FVector(1.0f));
		}
		else if (IconScale.X - 0.5 > 1.0f) {
			SelectedCharacterIcon->SetActorScale3D(FVector(1.0f));
		}
		SelectedCharacterIcon->ChangeMaterialColour(FVector4d(5.f, 10.f, 100.f, 0.5f));
	}
}
